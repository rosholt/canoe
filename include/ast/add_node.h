#ifndef CANOE_AST_ADD_NODE_H_
#define CANOE_AST_ADD_NODE_H_

#include "ast/node.h"
#include "builder_adaptor.h"

using namespace llvm;

class AddNode : public Node {
private:
  Node *left_;
  Node *right_;

public:
  AddNode(Node *left, Node *right);
  Value *BuildIR(BuilderAdaptor *adaptor = BuilderAdaptor::instance(), Scope *scope = new Scope);
};

#endif
