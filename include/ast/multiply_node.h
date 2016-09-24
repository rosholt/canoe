#ifndef JUGGERNAUT_AST_MULTIPLY_NODE_H_
#define JUGGERNAUT_AST_MULTIPLY_NODE_H_

#include "ast/node.h"
#include "builder_adaptor.h"

using namespace llvm;

class MultiplyNode : public Node {
private:
  Node *left_;
  Node *right_;

public:
  MultiplyNode(Node *left, Node *right);
  Value *BuildIR(BuilderAdaptor *adaptor = BuilderAdaptor::instance(), Scope *scope = new Scope);
};

#endif
