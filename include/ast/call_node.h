#ifndef CANOE_AST_CALL_NODE_H_
#define CANOE_AST_CALL_NODE_H_

#include "ast/node.h"
#include "ast/function_node.h"
#include "builder_adaptor.h"

using namespace std;
using namespace llvm;

class CallNode : public Node {
private:
  string *function_name_;
  vector<Node *> arguments_;

public:
  CallNode(string *function_name, vector<Node *> arguments);
  Value *BuildIR(BuilderAdaptor *adaptor = BuilderAdaptor::instance(), Scope *scope = new Scope);
};

#endif
