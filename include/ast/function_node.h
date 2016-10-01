#ifndef JUGGERNAUT_AST_FUNCTION_NODE_H_
#define JUGGERNAUT_AST_FUNCTION_NODE_H_

#include "ast/node.h"

using namespace std;
using namespace llvm;

struct FunctionSignature {
  string *name = NULL;
  int parameter_count = 0;
  string *parameter_array = NULL;
};

class FunctionNode {
  const FunctionSignature *signature_;
  Node *body_;

public:
  FunctionNode(FunctionSignature *signature, Node *body);
  Function *BuildIR(BuilderAdaptor *adaptor = BuilderAdaptor::instance(), Scope *scope = new Scope);
};

#endif
