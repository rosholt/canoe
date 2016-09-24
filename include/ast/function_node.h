#ifndef JUGGERNAUT_AST_FUNCTION_NODE_H_
#define JUGGERNAUT_AST_FUNCTION_NODE_H_

#include "ast/node.h"

using namespace std;
using namespace llvm;

class FunctionNode {
  const string *name_;
  Node *body_;

public:
  FunctionNode(string *name, Node *body);
  Function *BuildIR(BuilderAdaptor *adaptor = BuilderAdaptor::instance(), Scope *scope = new Scope);
};

#endif
