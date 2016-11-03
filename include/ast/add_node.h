#ifndef CANOE_AST_ADD_NODE_H_
#define CANOE_AST_ADD_NODE_H_

#include "ast/node.h"

class Expression;

class AddNode : public Node {
private:
  const std::unique_ptr<Expression> left_;
  const std::unique_ptr<Expression> right_;

public:
  AddNode(std::unique_ptr<Expression> left, std::unique_ptr<Expression> right);
  std::unique_ptr<ExpressionValue> BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const
      override;
};

#endif
