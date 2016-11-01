#ifndef CANOE_AST_MODULE_NODE_H_
#define CANOE_AST_MODULE_NODE_H_

class Value;

class ModuleNode : public Node {
private:
  const std::string name_;
  const std::vector<Node *> nodes_;

public:
  ModuleNode(const std::string name);
  Value *BuildIR(BuilderAdaptor *adaptor = BuilderAdaptor::instance(), Scope *scope = new Scope);
};

#endif
