#ifndef JUGGERNAUT_AST_NODE_H_
#define JUGGERNAUT_AST_NODE_H_

#include "llvm/IR/value.h"
#include "builder_adaptor.h"
#include "scope.h"

using namespace llvm;

class Node {
public:
  virtual Value *BuildIR(BuilderAdaptor *adaptor = BuilderAdaptor::instance(), Scope *scope = new Scope) = 0;
  virtual ~Node() {}
};

#endif
