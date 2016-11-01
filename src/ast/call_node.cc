#include "ast/call_node.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Value.h"
#include "scope.h"
#include "builder_adaptor.h"

CallNode::CallNode(std::string function_name, std::vector<Node *> arguments) :
    function_name_(function_name), arguments_(arguments) {
}


std::unique_ptr<llvm::Value> CallNode::BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const {
  // TODO: I thought that this was ellided?
  auto function = std::move(scope->named_functions[function_name_]);


  std::vector<llvm::Value *> argument_values;
  for (auto &arg : arguments_) {
    argument_values.push_back(arg->BuildIR(scope, adaptor).get());
  }

  return std::unique_ptr<llvm::Value>(adaptor->Builder()->CreateCall(function.get(), argument_values, "calltmp"));
}
