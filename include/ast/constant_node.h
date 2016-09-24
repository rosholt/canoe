#ifndef JUGGERNAUT_AST_CONSTANT_NODE_H_
#define JUGGERNAUT_AST_CONSTANT_NODE_H_

#include "ast/node.h"

using namespace llvm;

class ConstantNode : public Node {
private:
  int value_;

public:
  ConstantNode(int value);
  Value *BuildIR(BuilderAdaptor *adaptor = BuilderAdaptor::instance(), Scope *scope = new Scope);
};

#endif
