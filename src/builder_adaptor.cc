#include <memory>

#include "builder_adaptor.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"

BuilderAdaptor::BuilderAdaptor() {
  context_ = std::make_unique<llvm::LLVMContext>();
  builder_ = new llvm::IRBuilder<>(*context_.get());
}

BuilderAdaptor::BuilderAdaptor(llvm::IRBuilder<> *builder, std::unique_ptr<llvm::LLVMContext> context) :
    builder_(builder), context_(std::move(context)) {
}

BuilderAdaptor *BuilderAdaptor::instance() {
  if (instance_ == nullptr) {
    instance_ = new BuilderAdaptor();
  }

  return instance_;
}

llvm::IRBuilder<> *BuilderAdaptor::Builder() const {
  return builder_;
}

llvm::LLVMContext *BuilderAdaptor::Context() const {
  return context_.get();
}

BuilderAdaptor *BuilderAdaptor::instance_ = nullptr;
