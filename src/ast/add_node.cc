#include "ast/add_node.h"
#include "builder_adaptor.h"
#include "expression.h"
#include "expression_value.h"
#include "ast/module_node.h"
#include "ast/function_node.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"

AddNode::AddNode(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right) :
    left_(std::move(left)), right_(std::move(right)) {
}

std::unique_ptr<ExpressionValue> AddNode::BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const {
  auto leftValue = left_->BuildIR(scope, adaptor)->value();
  auto rightValue = right_->BuildIR(scope, adaptor)->value();

  auto value = std::unique_ptr<llvm::Value>(adaptor->Builder()->CreateAdd(leftValue.get(), rightValue.get(), "addtmp"));
  return std::make_unique<ExpressionValue>(std::move(value));
};
