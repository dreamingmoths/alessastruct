#ifndef ALESSASTRUCT_KAITAI_CONSUMER_H
#define ALESSASTRUCT_KAITAI_CONSUMER_H

#include "clang/AST/ASTConsumer.h"
#include "clang/AST/ASTContext.h"

#include "alessastruct/Alessastruct.h"
#include "alessastruct/KaitaiVisitor.h"

namespace alessastruct {
class Reader : public clang::ASTConsumer {
public:
  explicit Reader(clang::ASTContext* Context, AlessastructOptions& opts);

  void configure(clang::ASTContext* Context);

  virtual void HandleTranslationUnit(clang::ASTContext& Context) override;

private:
  alessastruct::KaitaiVisitor visitor;
  AlessastructOptions& options;
};
} // namespace alessastruct

#endif // ALESSASTRUCT_KAITAI_CONSUMER_H
