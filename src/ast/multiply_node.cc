#include "ast/multiply_node.h"

using namespace std;
using namespace llvm;

MultiplyNode::MultiplyNode(Node *left, Node *right) : left_(left), right_(right) {}

Value *MultiplyNode::BuildIR(BuilderAdaptor *adaptor, Scope *scope) {
  Value *leftValue = left_->BuildIR(adaptor, scope);
  Value *rightValue = right_->BuildIR(adaptor, scope);

  return adaptor->Builder()->CreateMul(leftValue, rightValue, "multmp");
}
