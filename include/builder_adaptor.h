#ifndef CANOE_BUILDER_ADAPTOR_H_
#define CANOE_BUILDER_ADAPTOR_H_

class llvm::IRBuilder;
class llvm::LLVMContext;

class BuilderAdaptor {
private:
  static BuilderAdaptor *instance_;
  llvm::IRBuilder<> *builder_;
  llvm::LLVMContext *context_;

  BuilderAdaptor();
  BuilderAdaptor(llvm::IRBuilder<> *builder, llvm::LLVMContext *context);
public:
  static BuilderAdaptor *instance();

  llvm::IRBuilder<> *Builder();
  llvm::LLVMContext *Context();
};

#endif
