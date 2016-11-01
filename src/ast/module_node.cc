#include <memory>

#include "ast/module_node.h"
#include "llvm/IR/Module.h"

ModuleNode::ModuleNode(const std::string name) : name_(name), nodes_(std::vector<Node *>()) {}

Value *ModuleNode::BuildIR(BuilderAdaptor *adaptor, Scope *scope) {
  auto module = new llvm::Module(name_, *adaptor->Context());

  // TODO: Should be an auto

  auto module_scope = new Scope;
  module_scope->module = scope->module;

  std::for_each(nodes_.begin(), nodes_.end(), [&](Node *n) {n->BuildIR(adaptor, module_scope);});

  return module;
};
