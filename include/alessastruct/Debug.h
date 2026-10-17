#ifndef ALESSASTRUCT_DEBUG_H
#define ALESSASTRUCT_DEBUG_H

#ifndef ALESSASTRUCT_DEBUG
#define ALESSASTRUCT_DEBUG 0
#endif

namespace alessastruct::debug {
void error(const char* errorMessage, ...);
}

#define alessaAssert(condition)                                                \
  do {                                                                         \
    static_assert(condition, "alessaAssert: " #condition);                     \
  } while (0)

#define alessaDebug(...)                                                       \
  do {                                                                         \
    if (ALESSASTRUCT_DEBUG)                                                    \
      fprintf(stderr, __VA_ARGS__);                                            \
  } while (0)

#define alessaWarn(...)                                                        \
  do {                                                                         \
    if (ALESSASTRUCT_DEBUG)                                                    \
      fprintf(stderr, "[warn]\t" __VA_ARGS__);                                 \
  } while (0)

#define alessaError(...)                                                       \
  do {                                                                         \
    alessastruct::debug::error("[error]\t" __VA_ARGS__);                       \
  } while (0)

#define alessaLogStream std::cout << "[info]\t"

#endif // ALESSASTRUCT_DEBUG_H
