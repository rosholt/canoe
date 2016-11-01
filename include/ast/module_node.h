#ifndef CANOE_AST_MODULE_NODE_H_
#define CANOE_AST_MODULE_NODE_H_

#include <string>
#include <vector>

namespace llvm {
class Module;
}

class BuilderAdaptor;
struct Scope;
class Node;

class ModuleNode {
private:
  const std::string name_;
  std::vector<Node *> nodes_;

public:
  ModuleNode(const std::string name);

  void append(Node *node);
  std::unique_ptr<llvm::Module> BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const;
};

#endif
