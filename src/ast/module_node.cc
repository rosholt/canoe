#include <memory>

#include "ast/module_node.h"
#include "builder_adaptor.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "ast/node.h"
#include "scope.h"

ModuleNode::ModuleNode(const std::string name) :
    name_(name), nodes_(std::vector<Node *>()) {
}

void ModuleNode::append(Node *node) {
  nodes_.push_back(node);
}

std::unique_ptr<llvm::Module> ModuleNode::BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const {
  auto module_scope = std::make_unique<Scope>();
  module_scope->module = std::make_unique<llvm::Module>(name_, *adaptor->Context());

  std::for_each(nodes_.begin(), nodes_.end(), [&](auto n) {n->BuildIR(module_scope, adaptor);});

  return std::move(module_scope->module);
};
