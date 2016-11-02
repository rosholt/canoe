#ifndef CANOE_EXPRESSION_H_
#define CANOE_EXPRESSION_H_

class FunctionNode;
class Node;
class ModuleNode;

enum class ExpressionType {
  FunctionExpression, ValueExpression, ModuleExpression
};

union ExpressionNode {
  std::unique_ptr<FunctionNode> function_node;
  std::unique_ptr<Node> value_node;
  std::unique_ptr<ModuleNode> module_node;
};

class Expression {
private:
  ExpressionType expression_type;
  ExpressionNode expression_node;

public:
  Expression(std::unique_ptr<FunctionNode> function_node);
  Expression(std::unique_ptr<Node> value_node);
  Expression(std::unique_ptr<ModuleNode> module_node);

  std::unique_ptr<llvm::Value> BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const;
};

#endif
