#include "ast/value_node.h"
#include "scope.h"
#include "builder_adaptor.h"
#include "expression_value.h"
#include "ast/module_node.h"
#include "ast/function_node.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"

ValueNode::ValueNode(std::string name) :
    name_(name) {
}

std::unique_ptr<ExpressionValue> ValueNode::BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const {
  return std::make_unique<ExpressionValue>(std::move(scope->named_values[name_]));
}
