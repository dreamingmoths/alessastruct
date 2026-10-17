#include <cstdarg>
#include <cstdio>
#include <cstdlib>

namespace alessastruct::debug {
[[noreturn]] void error(const char* errorMessage, ...) {
  va_list args;
  va_start(args, errorMessage);

  vfprintf(stderr, errorMessage, args);
  std::exit(1);

  va_end(args);
}
} // namespace alessastruct::debug
