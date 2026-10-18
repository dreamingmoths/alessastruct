
#include "clang/AST/ASTContext.h"
#include "clang/AST/PrettyPrinter.h"
#include "clang/AST/RecordLayout.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/AST/TypeBase.h"

#include "alessastruct/Debug.h"
#include "alessastruct/KaitaiSerializer.h"
#include "alessastruct/KaitaiVisitor.h"

using namespace clang;

namespace alessastruct {
KaitaiVisitor::KaitaiVisitor(ASTContext* Context)
    : Context(Context), policy(Context->getLangOpts()) {
  policy.SuppressTagKeyword = true;
}

bool KaitaiVisitor::VisitRecordDecl(RecordDecl* declaration) {
  if (declaration->getDefinition() != declaration) {
    // we only visit declarations that actually define things
    return true;
  }

  const ASTRecordLayout& layout = Context->getASTRecordLayout(declaration);

  // the name of the record before we convert it to Kaitai format
  const char* originalName = NULL;
  int originalNameLength = 0;

  // the standardized kaitai id for the type
  char nameBuffer[MAX_IDENTIFIER_SIZE] = "";
  const char* name = nameBuffer;

  /* to get the name, we'll try both `getName()` and `getDeclName()` */

  TypedefNameDecl* typedefNameDecl = declaration->getTypedefNameForAnonDecl();
  StringRef nameRef;
  std::string nameString;

  if (typedefNameDecl) {
    nameRef = typedefNameDecl->getName();
    originalNameLength = nameRef.size();
    originalName = nameRef.data();
  } else {
    nameString = declaration->getDeclName().getAsString();
    originalNameLength = nameString.size();
    originalName = nameString.c_str();
  }

  kaitaiSerializer->canonicalizeName(originalName, nameBuffer,
                                     originalNameLength);

  /* fallback to a generated name */
  if (!name || !*name) {
    RecordDecl* record = declaration->getDefinition();
    name = idCreator.getOrCreate(record, "").c_str();
  }

  debugPrintRecordDeclaration(declaration, layout, name);

  if (declaration->isEnum()) {
    /* @unhandled */
    return true;
  }

  onVisitStructOrUnion(declaration, layout, name);

  return true;
}

void KaitaiVisitor::onVisitStructOrUnion(RecordDecl* declaration,
                                         const ASTRecordLayout& layout,
                                         const char* name) {
  bool isStruct = declaration->isStruct();
  bool isUnion = declaration->isUnion();

  currentRecordName = name;

  kaitaiSerializer->beginRecord(name);

  if (isStruct) {
    kaitaiSerializer->beginRecord("seq");
  } else if (isUnion) {
    kaitaiSerializer->beginRecord("instances");
  }

  totalOffsetBits = 0;

  for (auto fieldDecl : declaration->fields()) {
    if (!(isStruct || isUnion))
      continue;

    onVisitField(fieldDecl, layout, name, isStruct);
  }

  if (isStruct) {
    alignToSize(layout.getSize().getQuantity(), totalOffsetBits);
  } else if (isUnion) {
    kaitaiSerializer->endRecord();
    kaitaiSerializer->beginRecord("seq");
    alignToSize(layout.getSize().getQuantity(), 0);
  }

  kaitaiSerializer->endRecord();
  kaitaiSerializer->endRecord();
}

void KaitaiVisitor::alignToSize(uint64_t sizeBytes, uint64_t offset) {
  uint64_t padding = sizeBytes * 8 - offset;


  if (padding > 0)
    kaitaiSerializer->writePadding(padding);
}


void KaitaiVisitor::onVisitField(FieldDecl* fieldDecl,
                                 const ASTRecordLayout& layout,
                                 const char* name, bool isStruct) {
  ASTContext& contextRef = *Context;

  auto fieldIndex = fieldDecl->getFieldIndex();
  auto fieldOffset = layout.getFieldOffset(fieldIndex);
  bool isBitField = fieldDecl->isBitField();

  QualType qualType = fieldDecl->getType().getCanonicalType();
  std::string qualTypeString = qualType.getAsString(policy);
  const char* qualTypeName = qualTypeString.c_str();
  bool isArray = qualType->isArrayType();

  TypeInfo typeInfo = contextRef.getTypeInfo(qualType);
  uint64_t fieldSizeBytes = typeInfo.Width / 8;

  int64_t alignOffset =
      getFieldAlignOffset(fieldDecl, typeInfo, fieldOffset, isStruct);

  ArrayDescription arrayDescription = getArrayDescription(contextRef, qualType);
  QualType valueType = arrayDescription.type;
  uint64_t repeatCount = arrayDescription.repeatCount;

  char typeName[MAX_IDENTIFIER_SIZE];
  fieldIsArray = isArray;
  fieldIsBitField = isBitField;
  getFieldTypeName(fieldDecl, valueType, qualTypeName, typeName);

  StringRef fieldDeclString = fieldDecl->getName();
  const char* uncanonicalizedName = fieldDeclString.data();
  uint16_t length = fieldDeclString.size();
  char fieldName[1024];
  kaitaiSerializer->canonicalizeName(uncanonicalizedName, fieldName, length);

  serializeField({
      .fieldName = fieldName,
      .typeName = typeName,
      .fieldSizeBytes = fieldSizeBytes,
      .repeatCount = repeatCount,
      .alignOffset = alignOffset,
      .isRecordStruct = isStruct,
      .isFieldUnion = qualType->isUnionType()
  });
}

void KaitaiVisitor::getFieldTypeName(FieldDecl* fieldDecl, QualType valueType,
                                     const char* fullTypeName, char* out) {
  ASTContext& context = *Context;

  QualType desugaredType =
      valueType.getDesugaredType(context).getCanonicalType();
  std::string desugaredTypeString = desugaredType.getAsString(policy);
  const char* desugaredTypeName = desugaredTypeString.c_str();

  TypeInfo desugaredTypeInfo = context.getTypeInfo(desugaredType);
  uint64_t desugaredTypeSize = fieldIsBitField ? fieldDecl->getBitWidthValue()
                                               : desugaredTypeInfo.Width >> 3;

  std::string typeString;
  auto* type = desugaredType.getTypePtr();
  bool shouldUsePointerType =
      kaitaiSerializer->USE_POINTER_TYPE && type->isAnyPointerType() &&
      type->getPointeeType().getTypePtr()->isRecordType();

  auto* underlyingType = desugaredType.getTypePtr();
  const char* kaitaiTypeName = NULL;
  const char* prettyName =
      (fieldIsArray && *desugaredTypeName) ? desugaredTypeName : fullTypeName;

  if (underlyingType->isRecordType() &&
      !underlyingType->getAsTagDecl()->hasNameForLinkage()) {
    RecordDecl* record = underlyingType->getAsRecordDecl()->getDefinition();
    typeString = idCreator.getOrCreate(record, currentRecordName);
    alessaDebug("name: %s\n", typeString.c_str());
  } else {
    std::string kaitaiTypeString = kaitaiSerializer->asKaitaiType(
        type, desugaredTypeSize, fieldIsBitField);
    kaitaiTypeName = kaitaiTypeString.c_str();

    alessaDebug("\nkaitai type: %s (%s)\n", kaitaiTypeName, desugaredTypeName);
    const char* unformattedTypeName =
        *kaitaiTypeName && !shouldUsePointerType ? kaitaiTypeName : prettyName;
    typeString = std::string(unformattedTypeName);
  }

  char buf[MAX_IDENTIFIER_SIZE];

  snprintf(out, typeString.length(), "%s", typeString.c_str());
  kaitaiSerializer->canonicalizeName(typeString.c_str(), out,
                                     typeString.size());
  if (type->isAnyPointerType()) {
    snprintf(buf, MAX_IDENTIFIER_SIZE, "pointer('%s')", out);
    snprintf(out, MAX_IDENTIFIER_SIZE, "%s", buf);
  }
}

int64_t KaitaiVisitor::getFieldAlignOffset(FieldDecl* fieldDecl,
                                           TypeInfo& typeInfo,
                                           uint64_t fieldOffset,
                                           bool isStruct) {
  uint64_t fieldSize =
      fieldDecl->isBitField() ? fieldDecl->getBitWidthValue() : typeInfo.Width;
  uint64_t newOffset = totalOffsetBits + fieldSize;
  int64_t targetAlignmentOffsetBits = fieldOffset - totalOffsetBits;

  if (isStruct && targetAlignmentOffsetBits != 0) {
    if (targetAlignmentOffsetBits < 0)
      alessaError("invalid alignment offset %llu", targetAlignmentOffsetBits);

    alessaDebug("misalignment: %llu vs %llu (new: %llu)", totalOffsetBits,
                fieldOffset, newOffset);
    newOffset += targetAlignmentOffsetBits;
  } else
    alessaDebug("aligned: %llu vs %llu (new: %llu)", totalOffsetBits,
                fieldOffset, newOffset);

  totalOffsetBits = newOffset;

  return targetAlignmentOffsetBits;
}

ArrayDescription getArrayDescription(ASTContext& context, QualType arrayType) {
  ArrayDescription description;

  QualType type = arrayType;

  bool isArray = type->isArrayType();
  bool isConstantArray = type->isConstantArrayType();

  uint64_t repeatCount = 1;

  if (isConstantArray) {
    while (type->isConstantArrayType()) {
      const ConstantArrayType* arrayType = context.getAsConstantArrayType(type);
      QualType next = arrayType->getElementType();
      repeatCount *= arrayType->getSize().getZExtValue();
      if (next == type)
        break;
      type = next;
    }
  } else if (isArray) {
    /* flexible array */
    while (type->isArrayType()) {
      const ArrayType* arrayType = context.getAsArrayType(type);
      QualType next = arrayType->getElementType();
      if (next == type)
        break;
      type = next;
    }
    repeatCount = 0;
  }

  description.type = type;
  description.repeatCount = repeatCount;

  return description;
}

void serializeField(FieldDescription&& description) {
  if (description.alignOffset > 0)
    kaitaiSerializer->writePadding(description.alignOffset);

  if (description.isRecordStruct) {
    kaitaiSerializer->beginAttributes();

    if (*description.fieldName) {
      kaitaiSerializer->writeAttributeProperty("id", description.fieldName);
    }

    kaitaiSerializer->writeAttributeProperty("type", description.typeName);

    if (description.isFieldUnion)
      kaitaiSerializer->writeAttributeProperty("size", description.fieldSizeBytes);

    if (description.repeatCount == 0) {
      kaitaiSerializer->writeAttributeProperty("repeat", "eos");
    } else if (description.repeatCount > 1) {
      kaitaiSerializer->writeAttributeProperty("repeat", "expr");
      kaitaiSerializer->writeAttributeProperty("repeat-expr",
                                               description.repeatCount);
    }

    kaitaiSerializer->endAttributes();
  } else /* if (declaration->isUnion()) */ {
    kaitaiSerializer->beginRecord(description.fieldName);
    kaitaiSerializer->writeKeyValue("pos", "0");
    kaitaiSerializer->writeKeyValue("type", description.typeName);

    if (description.repeatCount == 0) {
      kaitaiSerializer->beginAttributes();
      kaitaiSerializer->writeAttributeProperty("repeat", "eos");
      kaitaiSerializer->endAttributes();
    } else if (description.repeatCount > 1) {
      kaitaiSerializer->writeKeyValue("repeat", "expr");
      kaitaiSerializer->writeKeyValue("repeat-expr", description.repeatCount);
    }
    kaitaiSerializer->endRecord();
  }
}

void debugPrintRecordDeclaration(RecordDecl* declaration,
                                 const ASTRecordLayout& layout,
                                 const char* name) {
  if (!ALESSASTRUCT_DEBUG) {
    return;
  }

  const char* kindName = declaration->getKindName().data();
  uint64_t recordSize = layout.getSize().getQuantity();
  uint64_t recordAlignment = layout.getAlignment().getQuantity();
  uint32_t recordFieldCount = layout.getFieldCount();

  alessaDebug("⭐️ [declaration] %s (count: %d, size: %llu, alignment: %llu, "
              "kind: %s)\n",
              name, recordFieldCount, recordSize, recordAlignment, kindName);
}

std::string& RecordIdCreator::getOrCreate(RecordDecl* declaration,
                                         const char* prefix = "") {
  if (!unnamedRecords.count(declaration)) {
    const char* middle = *prefix ? "_anon_" : "anon_";
    unnamedRecords[declaration] =
        std::string(prefix) + middle + std::to_string(++recordIdCounter);
  }
  return unnamedRecords[declaration];
}
} // namespace alessastruct
