#ifndef CANOE_AST_VALUE_NODE_H_
#define CANOE_AST_VALUE_NODE_H_

#include <string>

#include "ast/node.h"

class ValueNode : public Node {
private:
  const std::string name_;

public:
  ValueNode(std::string name);
  std::unique_ptr<ExpressionValue> BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const override;
};

#endif
