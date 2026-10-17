#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <string>

#include "clang/AST/TypeBase.h"

namespace alessastruct {
class KaitaiSerializer {
public:
  KaitaiSerializer(FILE* f, const char* name);

  void writePrelude(void);

  void writeMetadata(void);

  void inc(void);

  void dec(void);

  void write(const char* format, ...);

  void writeKey(const char* key);

  void writeKeyValue(const char* field, const char* value);

  void writeKeyValue(const char* field, uint64_t value);

  void beginAnonymousAttribute(const char* key, const char* value);

  void writeAttributeProperty(const char* field, const char* value);

  void writeAttributeProperty(const char* field, uint64_t value);

  void beginRecord(const char* typeName);

  void endRecord(void);

  void beginAttributes(void);

  void endAttributes(void);

  void writeNewLine(void);

  void writeAfterword(void);

  void canonicalizeName(const char* name, char* result, uint16_t length);

  std::string asKaitaiType(const clang::Type* type, size_t size,
                           bool isBitfield);

  /**
   * Should we use a custom type for pointers, or parse them as numbers?
   */
  const bool USE_POINTER_TYPE = true;

  /**
   * \ref https://doc.kaitai.io/user_guide.html#param-types
   */
  const char* POINTER_PARAM_TYPE = "str";

private:
  /* essential */
  FILE* stream;
  const char* id;

  /* options */
  const char* ENDIAN = "le";
  const uint32_t INDENT_WIDTH = 2;
  const char* POINTER_KAITAI_TYPE = "u4";

  /* state */
  uint32_t indent = 0;
  uint32_t attributeCount = -1;

  bool alreadyWroteNewLine;

  bool needsU128Type;
  bool needsPointerType;

  /* helpers */
  bool isNewLineString(const char* string);
};

extern alessastruct::KaitaiSerializer* kaitaiSerializer;

#define MAX_TYPE_STRING_LENGTH 8
} // namespace alessastruct
