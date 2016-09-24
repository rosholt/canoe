#include "builder_adaptor.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

BuilderAdaptor::BuilderAdaptor() {
  context_ = new LLVMContext();
  builder_ = new IRBuilder<>(*context_);
}

BuilderAdaptor::BuilderAdaptor(IRBuilder<> *builder, LLVMContext *context) : builder_(builder), context_(context) {};

BuilderAdaptor *BuilderAdaptor::instance() {
  if (instance_ == NULL) {
    instance_ = new BuilderAdaptor();
  }
  
  return instance_;
//return NULL;
};

IRBuilder<> *BuilderAdaptor::Builder() {
  return builder_;
}

LLVMContext *BuilderAdaptor::Context() {
  return context_;
}

BuilderAdaptor *BuilderAdaptor::instance_ = 0;
