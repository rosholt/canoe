#include "ast/function_node.h"
#include "llvm/IR/Constants.h"
#include "llvm/ADT/APInt.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"

using namespace std;
using namespace llvm;

FunctionNode::FunctionNode(string *name, Node *body) : name_(name), body_(body) {};

Function *FunctionNode::BuildIR(BuilderAdaptor *adaptor, Scope *scope) {
  auto TheModule = new Module("juggernaut", *adaptor->Context());
  auto integer_type = adaptor->Builder()->getInt32Ty();
  vector<Type*> params(1, integer_type);
  FunctionType *function_type = FunctionType::get(integer_type, params, false);
  
  Function *function = Function::Create(function_type, Function::ExternalLinkage, *name_, TheModule);
  
  for (auto &arg : function->args()) {
    arg.setName("a");
    scope->named_values["a"] = &arg;
  }
  
  BasicBlock *block = BasicBlock::Create(*adaptor->Context(), "entry", function);
  adaptor->Builder()->SetInsertPoint(block);
  adaptor->Builder()->CreateRet(body_->BuildIR(adaptor, scope));
  verifyFunction(*function);

  return function;
};
