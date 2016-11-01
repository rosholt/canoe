#include "ast/call_node.h"
#include <iostream>

using namespace std;
using namespace llvm;

CallNode::CallNode(string *function_name, vector<Node *> arguments): function_name_(function_name), arguments_(arguments) {}

Value *CallNode::BuildIR(BuilderAdaptor *adaptor, Scope *scope) {
  /*
  FunctionNode *function_node = scope->named_functions[*function_name_];
  Function *function = function_node->BuildIR(adaptor, scope);
  */

  cout << *function_name_ << endl;
  Function *function = scope->named_functions[*function_name_];


  vector<Value *> argument_values;
  for (auto &arg : arguments_) {
    argument_values.push_back(arg->BuildIR(adaptor, scope));
  }

    cout << function << endl; fflush(stdout);
  cout << argument_values.size() << endl; fflush(stdout);
  return adaptor->Builder()->CreateCall(function, argument_values, "calltmp");
}
