#include "expression.h"

#include "ast/node.h"
#include "ast/module_node.h"
#include "ast/function_node.h"
#include "expression_value.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"

#include <iostream>
#include <memory>

Expression::Expression(std::unique_ptr<FunctionNode> function_node) {
  expression_type = ExpressionType::FunctionExpression;
  expression_node.function_node = std::move(function_node);
}

Expression::Expression(std::unique_ptr<Node> value_node) {
  expression_type = ExpressionType::ValueExpression;
  expression_node.value_node = std::move(value_node);
}

Expression::Expression(std::unique_ptr<ModuleNode> module_node) {
  expression_type = ExpressionType::ModuleExpression;
  expression_node.module_node = std::move(module_node);
}

//Expression::~Expression() {
//  switch (expression_type) {
//    case ExpressionType::ValueExpression:
//    expression_node.value_node.reset();
//    case ExpressionType::FunctionExpression:
//    expression_node.function_node.node.reset();
//    case ExpressionType::ModuleExpression:
//    expression_node.module_node.reset();
//  }
//}

std::unique_ptr<ExpressionValue> Expression::BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const {
  switch (expression_type) {
  case ExpressionType::ValueExpression:
    std::cout << "Expression resolves to value" << std::endl;
    return expression_node.value_node->BuildIR(scope, adaptor);
  case ExpressionType::FunctionExpression:
    std::cout << "Expression resolves to function" << std::endl;
    return expression_node.function_node->BuildIR(scope, adaptor);
  case ExpressionType::ModuleExpression:
    std::cout << "Expression resolves to module" << std::endl;
    return expression_node.module_node->BuildIR(scope, adaptor);
  default:
    std::cout << "Expression resolution failed" << std::endl;
    return nullptr;
  }
}
