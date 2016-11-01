#ifndef CANOE_AST_NODE_H_
#define CANOE_AST_NODE_H_

class llvm::Value;
class BuilderAdaptor;
class Scope;

using namespace llvm;

class Node {
public:
  virtual std::unique_ptr<Value> BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor =
      BuilderAdaptor::instance()) const = 0;
  virtual ~Node() {}
};

#endif
