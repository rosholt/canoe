#ifndef CANOE_AST_NODE_H_
#define CANOE_AST_NODE_H_

#include <memory>

namespace llvm {
	class Value;
}

class BuilderAdaptor;
struct Scope;

class Node {
public:
  virtual std::unique_ptr<llvm::Value> BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const = 0;
  virtual ~Node() {}
};

#endif
