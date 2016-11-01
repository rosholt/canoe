#ifndef CANOE_AST_FUNCTION_NODE_H_
#define CANOE_AST_FUNCTION_NODE_H_

#include "ast/node.h"

struct FunctionSignature {
  const std::string name;
  const std::vector<std::string> parameters;
};

class FunctionNode {
  const std::unique_ptr<FunctionSignature> signature_;
  const std::unique_ptr<Node> body_;

public:
  FunctionNode(const std::unique_ptr<FunctionSignature> signature, const std::unique_ptr<Node> *body);
  std::unique_ptr<Value> BuildIR(const std::unique_ptr<Scope> scope, const BuilderAdaptor *adaptor = BuilderAdaptor::instance()) const override;
};

#endif
