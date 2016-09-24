#ifndef JUGGERNAUT_BUILDER_ADAPTOR_H_
#define JUGGERNAUT_BUILDER_ADAPTOR_H_

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"

using namespace llvm;

class BuilderAdaptor {
private:
  static BuilderAdaptor *instance_;
  IRBuilder<> *builder_;
  LLVMContext *context_;
  
  BuilderAdaptor();
  BuilderAdaptor(IRBuilder<> *builder, LLVMContext *context);
public:
  static BuilderAdaptor *instance();
  
  IRBuilder<> *Builder();
  LLVMContext *Context();
};

#endif