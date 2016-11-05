#ifndef CANOE_BUILDER_ADAPTOR_H_
#define CANOE_BUILDER_ADAPTOR_H_

#include <memory>

// TODO: This should be forward declared, with the weird templating
#include "llvm/IR/IRBuilder.h"

namespace llvm {
class LLVMContext;
}

class BuilderAdaptor {
private:
  static BuilderAdaptor *instance_;
  llvm::IRBuilder<> *builder_;
  std::unique_ptr<llvm::LLVMContext> context_;

  BuilderAdaptor();
  BuilderAdaptor(llvm::IRBuilder<> *builder, std::unique_ptr<llvm::LLVMContext> context);

public:
  static BuilderAdaptor *instance();

  llvm::IRBuilder<> *Builder() const;
  llvm::LLVMContext *Context() const;
};

#endif
