#ifndef CANOE_AST_FUNCTION_NODE_H_
#define CANOE_AST_FUNCTION_NODE_H_

#include <string>
#include <vector>

namespace llvm {
class Function;
}

class Node;
class BuilderAdaptor;
struct Scope;

struct FunctionSignature {
  std::string name;
  std::vector<std::string> parameters;
};

class FunctionNode {
private:
  const std::unique_ptr<FunctionSignature> signature_;
  const std::unique_ptr<Node> body_;

public:
  FunctionNode(std::unique_ptr<FunctionSignature> signature, std::unique_ptr<Node> body);
  std::unique_ptr<llvm::Function> BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const;
};

#endif
