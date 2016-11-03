#include <iostream>
#include <memory>

#include "ast/constant_node.h"
#include "builder_adaptor.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Value.h"
#include "expression_value.h"

using namespace llvm;

ConstantNode::ConstantNode(int value) : value_(value) {}

std::unique_ptr<ExpressionValue> ConstantNode::BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const {
  auto value = std::unique_ptr<llvm::Value>(adaptor->Builder()->getInt32(value_));
  return std::make_unique<ExpressionValue>(std::move(value));
}
