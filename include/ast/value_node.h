#ifndef CANOE_AST_VALUE_NODE_H_
#define CANOE_AST_VALUE_NODE_H_

#include "ast/node.h"
#include <string>

using namespace std;
using namespace llvm;

class ValueNode : public Node {
private:
  string *name_;

public:
  ValueNode(string *name);
  Value *BuildIR(BuilderAdaptor *adaptor = BuilderAdaptor::instance(), Scope *scope = new Scope);
};

#endif
