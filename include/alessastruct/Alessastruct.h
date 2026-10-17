#ifndef ALESSASTRUCT_H
#define ALESSASTRUCT_H

#include <filesystem>

namespace alessastruct {
namespace fs = std::filesystem;

enum class Platform : uint32_t {
  /**
   * No target-specific configuration will be applied. The user is
   * required to pass arguments to `clang` to configure the output.
   */
  Unknown,

  /**
   * PlayStation 2 configuration. Uses a hack to force 32-bit pointers
   * while maintaining 64-bit `long`.
   */
  PS2
};

class AlessastructOptions {
public:
  /**
   * \see alessastruct::Platform
   */
  Platform platform = Platform::PS2;

  /**
   * A C-style identifier string to name the result.
   */
  const char* id;

  /**
   * Path to the output file.
   */
  fs::path outputPath = "output.yaml";

  AlessastructOptions(const char* name = "alessastruct");
};
} // namespace alessastruct

#endif // ALESSASTRUCT_H
