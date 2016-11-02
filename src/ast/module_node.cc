#include <iostream>
#include <memory>

#include "ast/module_node.h"
#include "builder_adaptor.h"
#include "expression.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Module.h"
#include "ast/node.h"
#include "scope.h"

ModuleNode::ModuleNode(const std::string name) :
    name_(name), expressions_(std::vector<Node *>()) {
}

void ModuleNode::append(Expression *expression) {
  expressions_.push_back(expression);
}

std::unique_ptr<llvm::Module> ModuleNode::BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const {
  std::cout << "[Module " << name_ << "] Generating IR" << std::endl;
  fflush(stdout);

  auto module_scope = std::make_unique<Scope>();
  module_scope->module = std::make_unique<llvm::Module>(name_, *adaptor->Context());

  std::for_each(expressions_.begin(), expressions_.end(), [&](auto e) {e->BuildIR(module_scope, adaptor);});

  return std::move(module_scope->module);
};
