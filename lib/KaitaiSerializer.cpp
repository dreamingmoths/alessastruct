#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <string>

#include "clang/AST/TypeBase.h"

#include "alessastruct/Character.h"
#include "alessastruct/KaitaiSerializer.h"

using namespace alessastruct;

/**
 * @note the KaitaiSerializer design is only a prototype at the moment, it is
 * likely to change in the future
 */

namespace alessastruct {
KaitaiSerializer* kaitaiSerializer;

KaitaiSerializer::KaitaiSerializer(FILE* f, const char* name) {
  id = name;
  stream = f;
}

void KaitaiSerializer::writePrelude(void) {
  writeMetadata();
  writeKey("types");
  inc();
}

void KaitaiSerializer::writeMetadata(void) {
  beginRecord("meta");
  writeKeyValue("id", id);
  writeKeyValue("endian", ENDIAN);
  writeKeyValue("bit-endian", ENDIAN);
  endRecord();
}

void KaitaiSerializer::inc(void) { indent += INDENT_WIDTH; }

void KaitaiSerializer::dec(void) { indent -= INDENT_WIDTH; }

void KaitaiSerializer::write(const char* format, ...) {
  va_list args;
  va_start(args, format);

  if (isNewLineString(format)) {
    if (alreadyWroteNewLine)
      return;
    alreadyWroteNewLine = true;
  } else
    alreadyWroteNewLine = false;

  vfprintf(stream, format, args);
  va_end(args);
}

void KaitaiSerializer::writeKey(const char* key) {
  write("%*s%s:\n", indent, "", key);
}

void KaitaiSerializer::writeKeyValue(const char* field, const char* value) {
  write("%*s%s: %s\n", indent, "", field, value);
}

void KaitaiSerializer::writeKeyValue(const char* field, uint64_t value) {
  write("%*s%s: %d\n", indent, "", field, value);
}

void KaitaiSerializer::beginAnonymousAttribute(const char* key,
                                               const char* value) {
  write("%*s- %s: %s\n", indent, "", key);
}

void KaitaiSerializer::writeAttributeProperty(const char* field,
                                              const char* value) {
  write("%*s%s %s: %s\n", indent, "", attributeCount > 0 ? " " : "-", field,
        value);
  attributeCount++;
}

void KaitaiSerializer::writeAttributeProperty(const char* field,
                                              uint64_t value) {
  write("%*s%s %s: %d\n", indent, "", attributeCount > 0 ? " " : "-", field,
        value);
}

void KaitaiSerializer::beginRecord(const char* typeName) {
  writeKey(typeName);
  inc();
}

void KaitaiSerializer::endRecord(void) {
  dec();
  writeNewLine();
}

void KaitaiSerializer::beginAttributes(void) { attributeCount = 0; }

void KaitaiSerializer::endAttributes(void) {
  attributeCount = -1;
  writeNewLine();
}

void KaitaiSerializer::writeNewLine(void) { write("\n"); }

void KaitaiSerializer::writeAfterword(void) {
  if (needsU128Type) {
    beginRecord("u16");
    beginRecord("seq");
    beginAttributes();
    writeAttributeProperty("id", "bytes");
    writeAttributeProperty("size", 16);
    endAttributes();
    endRecord();
    endRecord();
  }

  if (needsPointerType) {
    beginRecord("pointer");
    beginRecord("params");
    beginAttributes();
    writeAttributeProperty("id", "to");
    writeAttributeProperty("type", POINTER_PARAM_TYPE);
    endAttributes();
    endRecord();

    beginRecord("seq");
    beginAttributes();
    writeAttributeProperty("id", "address");
    writeAttributeProperty("type", POINTER_KAITAI_TYPE);
    endAttributes();
    endRecord();
    endRecord();
  }
}

void KaitaiSerializer::canonicalizeName(const char* name, char* result,
                                        uint16_t length) {
  int i = 0, j = 0;
  bool hasWrittenUnderscore = false;

  while (!isAlphabeticalCharacter(name[i]) && i < length)
    i++;

  for (; i < length; i++) {

    char c = name[i];

    if (!c)
      break;

    bool isLower = isLowercaseCharacter(c);
    bool isUpper = isUppercaseCharacter(c);
    bool isDigit = isDigitCharacter(c);
    bool isUnderscore = c == '_';

    if (!(isLower || isUpper || isDigit || isUnderscore))
      continue;

    bool writeUnderscoreBefore = false;

    if (j > 0 && isUnderscore) {
      if (hasWrittenUnderscore)
        continue;
      hasWrittenUnderscore = true;
    } else if (j > 0 && isUpper &&
              ((i < length - 1 && isLowercaseCharacter(name[i + 1])) ||
               (i > 0 && isLowercaseCharacter(name[i - 1])))) {
      writeUnderscoreBefore = !hasWrittenUnderscore;
      hasWrittenUnderscore = writeUnderscoreBefore;
    } else if (!isUnderscore) {
      hasWrittenUnderscore = false;
    }

    if (writeUnderscoreBefore)
      result[j++] = '_';
    result[j++] = toLowerCharacter(c);
  }

  result[j] = 0;
}

std::string KaitaiSerializer::asKaitaiType(const clang::Type* type, size_t size,
                                           bool isBitfield) {
  char primitiveType[MAX_TYPE_STRING_LENGTH] = "";
  bool isPointer = type->isAnyPointerType();

  if (isPointer) {
    snprintf(primitiveType, sizeof("data"), "data");

    if (USE_POINTER_TYPE)
      needsPointerType = true;
  } else {
    if (type->isFloatingType()) {
      primitiveType[0] = 'f';
    } else if (!type->hasIntegerRepresentation()) {
      return std::string("");
    } else {
      if (size == 16) {
        this->needsU128Type = true;
        return std::string("u16");
      }

          primitiveType[0] = !isBitfield
            ? type->isUnsignedIntegerType() ? 'u' : 's'
            : 'b';
    }

    snprintf(primitiveType + 1, MAX_TYPE_STRING_LENGTH - 1, "%zu", size);
  }

  return std::string(primitiveType);
}

bool KaitaiSerializer::isNewLineString(const char* string) {
  return string[0] == '\n' && string[1] == '\0';
}
} // namespace alessastruct
