#include "ast/constant_node.h"
#include <iostream>

using namespace llvm;

ConstantNode::ConstantNode(int value) : value_(value) {}

Value *ConstantNode::BuildIR(BuilderAdaptor *adaptor, Scope *scope) {
  return adaptor->Builder()->getInt32(value_);
}
