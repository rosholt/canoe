#ifndef CANOE_AST_CALL_NODE_H_
#define CANOE_AST_CALL_NODE_H_

#include <string>
#include <vector>
#include "ast/node.h"

class Expression;
class Expressionvalue;

class CallNode : public Node {
private:
  const std::string function_name_;
  const std::vector<std::unique_ptr<Expression>> arguments_;

public:
  CallNode(std::string function_name, std::vector<std::unique_ptr<Expression>> arguments);
  std::unique_ptr<ExpressionValue> BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const
      override;
};

#endif
