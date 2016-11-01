#ifndef CANOE_AST_ADD_NODE_H_
#define CANOE_AST_ADD_NODE_H_

#include "ast/node.h"

class AddNode : public Node {
private:
  const std::unique_ptr<Node> left_;
  const std::unique_ptr<Node> right_;

public:
  AddNode(std::unique_ptr<Node> left, std::unique_ptr<Node> right);
  std::unique_ptr<llvm::Value> BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const
      override;
};

#endif
