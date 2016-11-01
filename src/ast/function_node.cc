#include "ast/function_node.h"
#include "builder_adaptor.h"
#include "llvm/IR/Constants.h"
#include "llvm/ADT/APInt.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Verifier.h"

FunctionNode::FunctionNode(const std::unique_ptr<FunctionSignature> signature, const std::unique_ptr<Node> *body) :
    signature_(signature), body_(body) {
}

std::unique_ptr<Value> FunctionNode::BuildIR(const std::unique_ptr<Scope> scope, const BuilderAdaptor *adaptor) const {
  auto integer_type = adaptor->Builder()->getInt32Ty();

  FunctionType *function_type;
  if (signature_->parameter_count > 0) {
    vector<Type*> params(1, integer_type);
    function_type = FunctionType::get(integer_type, params, false);
  } else {
    function_type = FunctionType::get(integer_type, false);
  }

  Function *function = Function::Create(function_type, Function::ExternalLinkage, *signature_->name, TheModule);

  int parameter_index = 0;
  for (auto &arg : function->args()) {
    auto parameter_name = signature_->parameter_array[parameter_index++];
    arg.setName(parameter_name);
    scope->named_values[parameter_name] = &arg;
  }

  BasicBlock *block = BasicBlock::Create(*adaptor->Context(), "entry", function);
  adaptor->Builder()->SetInsertPoint(block);
  adaptor->Builder()->CreateRet(body_->BuildIR(adaptor, scope));
  verifyFunction(*function);
  scope->named_functions[*signature_->name] = function;

  return function;
};
