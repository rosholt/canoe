#include "builder_adaptor.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"

BuilderAdaptor::BuilderAdaptor() {
  context_ = std::make_unique<llvm::LLVMContext>();
  builder_ = std::make_unique<llvm::IRBuilder<>>(context_);
}

BuilderAdaptor::BuilderAdaptor(llvm::IRBuilder<> *builder, llvm::LLVMContext *context) :
    builder_(builder), context_(context) {
}

std::unique_ptr<BuilderAdaptor> BuilderAdaptor::instance() {
  if (instance_ == NULL) {
    instance_ = new BuilderAdaptor();
  }

  return instance_;
}

llvm::IRBuilder<> *BuilderAdaptor::Builder() {
  return builder_;
}

llvm::LLVMContext *BuilderAdaptor::Context() {
  return context_;
}

BuilderAdaptor *BuilderAdaptor::instance_ = 0;
