#include "ast/value_node.h"
#include "scope.h"
#include "builder_adaptor.h"

ValueNode::ValueNode(std::string name) :
    name_(name) {
}

std::unique_ptr<llvm::Value> ValueNode::BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const {
  return std::move(scope->named_values[name_]);
}
