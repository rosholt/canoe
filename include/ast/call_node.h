#ifndef CANOE_AST_CALL_NODE_H_
#define CANOE_AST_CALL_NODE_H_

#include <string>
#include <vector>
#include "ast/node.h"

class CallNode : public Node {
private:
  std::string function_name_;
  std::vector<Node *> arguments_;

public:
  CallNode(std::string function_name, std::vector<Node *> arguments);
  std::unique_ptr<llvm::Value> BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const
      override;
};

#endif
