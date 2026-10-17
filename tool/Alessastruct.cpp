#include <filesystem>
#include <iostream>
#include <sstream>

#include "clang/Frontend/FrontendActions.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Tooling.h"

#include "llvm/Support/CommandLine.h"

#include "alessastruct/Alessastruct.h"
#include "alessastruct/Debug.h"
#include "alessastruct/Reader.h"

using namespace clang;
using namespace clang::tooling;

namespace alessastruct {
namespace cl = llvm::cl;
namespace fs = std::filesystem;

static cl::OptionCategory AlessastructCategory("Alessastruct");

static cl::opt<std::string> OutputPath{
    "output",
    cl::desc("Specify an output path."),
    cl::ValueOptional,
    cl::cat(AlessastructCategory),
};

static cl::opt<Platform> TargetPlatform{
    "platform",
    cl::desc("Specify a target platform."),
    cl::values(
          clEnumValN(Platform::Unknown, "unknown", "Will not perform any platform-specific configuration."),
          clEnumValN(Platform::PS2, "ps2", "PlayStation 2 configuration; forces 32-bit pointers.")),
    cl::ValueOptional,
    cl::init(Platform::Unknown),
    cl::cat(AlessastructCategory),
};

  static cl::extrahelp MoreHelp("\nAlessastruct is a tool that converts C data types to Kaitai Struct.\n");

AlessastructOptions::AlessastructOptions(const char* name) : id(name) {
  std::string& pathString = OutputPath.getValue();

  if (pathString.length()) {
    this->outputPath.assign(pathString);

    if (!fs::is_directory(this->outputPath.parent_path()))
      fs::create_directories(this->outputPath.parent_path());
  } else
    this->outputPath.assign(name).concat(".ksy");

  this->platform = TargetPlatform.getValue();
}

class AlessastructAction : public ASTFrontendAction {
public:
  virtual std::unique_ptr<ASTConsumer>
  CreateASTConsumer(CompilerInstance& Compiler,
                    llvm::StringRef InFile) override {
    options = AlessastructOptions(createIdentifier(InFile));

    return std::make_unique<Reader>(
      &Compiler.getASTContext(),
      options
    );
  }

private:
  AlessastructOptions options;
  fs::path basename;

  const char* createIdentifier(llvm::StringRef ref) {
    basename = fs::path(ref.data()).stem();
    return basename.c_str();
  }
};

void configure(ClangTool& Tool) {
  Tool.appendArgumentsAdjuster(getClangSyntaxOnlyAdjuster());

  if (TargetPlatform.getValue() == Platform::PS2)
      Tool.appendArgumentsAdjuster(getInsertArgumentAdjuster("--target=mips64el", ArgumentInsertPosition::END));
}
} // namespace alessastruct

int main(int argc, const char** argv) {
  auto ExpectedParser = CommonOptionsParser::create(
      argc, argv, alessastruct::AlessastructCategory);
  if (!ExpectedParser) {
    llvm::errs() << ExpectedParser.takeError();
    return 1;
  }

  CommonOptionsParser& OptionsParser = ExpectedParser.get();
  ClangTool Tool(OptionsParser.getCompilations(),
                 OptionsParser.getSourcePathList());

  alessastruct::configure(Tool);

  return Tool.run(
      newFrontendActionFactory<alessastruct::AlessastructAction>().get());
}
