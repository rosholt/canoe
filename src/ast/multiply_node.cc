#include <memory>

#include "ast/multiply_node.h"
#include "builder_adaptor.h"
#include "llvm/IR/IRBuilder.h"

MultiplyNode::MultiplyNode(std::unique_ptr<Node> left, std::unique_ptr<Node> right) :
    left_(std::move(left)), right_(std::move(right)) {
}

std::unique_ptr<llvm::Value> MultiplyNode::BuildIR(std::unique_ptr<Scope> const &scope, std::unique_ptr<BuilderAdaptor> const &adaptor) const {
  auto leftValue = left_->BuildIR(scope, adaptor);
  auto rightValue = right_->BuildIR(scope, adaptor);

  return std::unique_ptr<llvm::Value>(adaptor->Builder()->CreateMul(leftValue.get(), rightValue.get(), "multmp"));
}
