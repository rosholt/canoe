#ifndef CANOE_AST_CONSTANT_NODE_H_
#define CANOE_AST_CONSTANT_NODE_H_

#include "ast/node.h"

class ConstantNode : public Node {
private:
  int value_;

public:
  ConstantNode(int value);
  std::unique_ptr<llvm::Value> BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const override;
};

#endif
