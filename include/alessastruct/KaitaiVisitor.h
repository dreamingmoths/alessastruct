#ifndef ALESSASTRUCT_KAITAI_VISITOR_H
#define ALESSASTRUCT_KAITAI_VISITOR_H

#include "clang/AST/ASTContext.h"
#include "clang/AST/RecursiveASTVisitor.h"

namespace alessastruct {
typedef struct ArrayDescription {
  clang::QualType type;
  uint64_t repeatCount;
} ArrayDescription;

typedef struct FieldDescription {
  const char* fieldName;
  const char* typeName;
  uint64_t repeatCount;
  int64_t alignOffset;
  bool isStruct;
} FieldDescription;

class RecordIdCreator {
public:
  std::string& getOrCreate(clang::RecordDecl* declaration, const char* prefix);

private:
  std::unordered_map<clang::RecordDecl*, std::string> unnamedRecords;
  uint32_t recordIdCounter = 0;
};

class KaitaiVisitor : public clang::RecursiveASTVisitor<KaitaiVisitor> {
public:
  explicit KaitaiVisitor(clang::ASTContext* Context);

  bool VisitRecordDecl(clang::RecordDecl* declaration);

  void onVisitStructOrUnion(clang::RecordDecl* declaration,
                            const clang::ASTRecordLayout& layout,
                            const char* name);
  void onVisitField(clang::FieldDecl* declaration,
                    const clang::ASTRecordLayout& layout, const char* name,
                    bool isStruct);
  int64_t getFieldAlignOffset(clang::FieldDecl* fieldDecl,
                              clang::TypeInfo& typeInfo, uint64_t fieldOffset,
                              bool isStruct);
  void getFieldTypeName(clang::FieldDecl* fieldDecl, clang::QualType valueType,
                        const char* fullTypeName, char* out);
  void alignToSize(uint64_t size);

private:
  clang::ASTContext* Context;
  clang::PrintingPolicy policy;

  RecordIdCreator idCreator;

  uint64_t totalOffsetBits = 0;
  const char* currentRecordName;
  bool fieldIsArray;
  bool fieldIsBitField;
};

ArrayDescription getArrayDescription(clang::ASTContext& context,
                                     clang::QualType arrayType);
void serializeField(FieldDescription&& description);
void debugPrintRecordDeclaration(clang::RecordDecl* declaration,
                                 const clang::ASTRecordLayout& layout,
                                 const char* name);

#define MAX_IDENTIFIER_SIZE 512
} // namespace alessastruct

#endif
