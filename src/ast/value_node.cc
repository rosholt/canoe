#include "ast/value_node.h"

using namespace llvm;

ValueNode::ValueNode(string *name) : name_(name) {}

Value *ValueNode::BuildIR(BuilderAdaptor *adaptor, Scope *scope) {
  return scope->named_values[*name_];
}
