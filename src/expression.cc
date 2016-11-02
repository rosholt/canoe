#include "expression.h"

#import "ast/node.h"
#import "ast/module_node.h"
#import "ast/function_node.h"

Expression::Expression(std::unique_ptr<FunctionNode> function_node) {
  expression_type = FunctionExpression;
  expression_node.function_node = std::move(function_node);
}

Expression::Expression(std::unique_ptr<Node> value_node) {
  expression_type = ValueExpression;
  expression_node.value_node = std::move(value_node);
}

Expression::Expression(std::unique_ptr<ModuleNode> module_node) {
  expression_type = ModuleExpression;
  expression_node.module_node = std::move(module_node);
}

std::unique_ptr<llvm::Value> Expression::BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const {
  switch (expression_type) {
  case ValueExpression:
    return expression_node.value_node->BuildIR(scope, adaptor);
  case FunctionExpression:
    return expression_node.function_node->BuildIR(scope, adaptor);
  case ModuleExpression:
    return expression_node.module_node->BuildIR(scope, adaptor);
  default:
    return nullptr;
  }
}
