#include "ast/add_node.h"

using namespace std;
using namespace llvm;

AddNode::AddNode(Node *left, Node *right) : left_(left), right_(right) {}

Value *AddNode::BuildIR(BuilderAdaptor *adaptor, Scope *scope) {
  Value *leftValue = left_->BuildIR(adaptor, scope);
  Value *rightValue = right_->BuildIR(adaptor, scope);

  return adaptor->Builder()->CreateAdd(leftValue, rightValue, "addtmp");
};
