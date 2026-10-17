#include <iostream>

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"

#include "clang/Basic/TargetInfo.h"

#include "alessastruct/Debug.h"
#include "alessastruct/KaitaiSerializer.h"
#include "alessastruct/KaitaiVisitor.h"
#include "alessastruct/Reader.h"

using namespace clang;

namespace alessastruct {
Reader::Reader(ASTContext* Context, AlessastructOptions& opts)
    : visitor(Context), options{opts} {
  configure(Context);
}

void Reader::configure(ASTContext* Context) {
  switch (options.platform) {
  case Platform::Unknown:
    break;

  case Platform::PS2:
    auto& info = const_cast<TargetInfo&>(Context->getTargetInfo());
    info.PointerWidth = info.PointerAlign = 32;
  }
}

void Reader::HandleTranslationUnit(clang::ASTContext& Context) {
  if (ALESSASTRUCT_DEBUG)
    Context.getTranslationUnitDecl()->dump();

  FILE* f = fopen(options.outputPath.c_str(), "w");

  kaitaiSerializer = new KaitaiSerializer(f, options.id);
  kaitaiSerializer->writePrelude();
  visitor.TraverseDecl(Context.getTranslationUnitDecl());
  kaitaiSerializer->writeAfterword();

  fclose(f);
}
} // namespace alessastruct
