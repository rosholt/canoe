#include <algorithm>
#include <iostream>
#include <memory>
#include <typeinfo>

#include "ast/function_node.h"
#include "ast/node.h"
#include "builder_adaptor.h"
#include "expression.h"
#include "llvm/IR/Constants.h"
#include "llvm/ADT/APInt.h"
#include "llvm/IR/Argument.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "scope.h"
#include "expression_value.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/IR/Function.h"
#include "ast/module_node.h"

// TODO: THis should be an array of nodes for a "body_expressions"
FunctionNode::FunctionNode(std::unique_ptr<FunctionSignature> signature, std::unique_ptr<Expression> body) :
    signature_(std::move(signature)), body_(std::move(body)) {
  std::cout << "Creating function " << signature_->name << std::endl;
  fflush(stdout);
}

std::unique_ptr<ExpressionValue> FunctionNode::BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const {
  std::cout << "[Function " << scope->module->getModuleIdentifier() << "." << signature_->name << "] Generating IR" << std::endl;
  fflush(stdout);

  auto integer_type = adaptor->Builder()->getInt32Ty();

  std::vector<llvm::Type *> params;
  std::transform(signature_->parameters.begin(), signature_->parameters.end(), params.begin(), [&](auto p) {return integer_type;});
  auto function_type = llvm::FunctionType::get(integer_type, params, false);

  llvm::Function *function = llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, signature_->name, scope->module.get());

  int parameter_index = 0;
  for (auto &arg : function->args()) {
    auto parameter_name = signature_->parameters[parameter_index++];
    arg.setName(parameter_name);
    scope->named_values[parameter_name] = std::unique_ptr<llvm::Argument>(&arg);
  }

  llvm::BasicBlock *block = llvm::BasicBlock::Create(*adaptor->Context(), "entry", function);
  adaptor->Builder()->SetInsertPoint(block);
  std::cout << 1 << std::endl;
  fflush(stdout);
  auto ret = body_->BuildIR(scope, adaptor)->value();
  std::cout << 2 << std::endl;
  fflush(stdout);
  std::cout << 3 << ret << std::endl;
  fflush(stdout);
  adaptor->Builder()->CreateRet(ret);
  std::cout << 4 << std::endl;
  fflush(stdout);
  std::cout << "[Function " << signature_->name << "] Verifying" << std::endl;
  fflush(stdout);
  verifyFunction(*function);
  std::cout << "[Function " << signature_->name << "] Verification Complete" << std::endl;
  fflush(stdout);
  scope->named_functions[signature_->name] = std::unique_ptr<llvm::Function>(function);

  std::cout << "[Function " << signature_->name << "] IR Generation Complete" << std::endl;
  return std::make_unique<ExpressionValue>(std::unique_ptr<llvm::Function>(function));
//  return nullptr;
}
