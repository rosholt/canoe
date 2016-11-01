#include <iostream>

#include "ast/constant_node.h"
#include "builder_adaptor.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;

ConstantNode::ConstantNode(int value) : value_(value) {}

std::unique_ptr<llvm::Value> ConstantNode::BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const {
  return std::unique_ptr<llvm::Value>(adaptor->Builder()->getInt32(value_));
}
