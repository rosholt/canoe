#include "expression_value.h"

#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"

ExpressionValue::ExpressionValue(std::unique_ptr<llvm::Function> function) :
    expression_value_type_(ExpressionValueType::FunctionValue) {
  expression_value_result_.function = std::move(function);
}

ExpressionValue::ExpressionValue(std::unique_ptr<llvm::Value> value) :
    expression_value_type_(ExpressionValueType::ValueValue) {
  expression_value_result_.value = std::move(value);
}

ExpressionValue::ExpressionValue(std::unique_ptr<llvm::Module> module) :
    expression_value_type_(ExpressionValueType::ModuleValue) {
  expression_value_result_.module = std::move(module);
}

void ExpressionValue::dump() {
  switch (expression_value_type_) {
  case ExpressionValueType::FunctionValue:
    expression_value_result_.function->dump();
    break;
  case ExpressionValueType::ValueValue:
    expression_value_result_.value->dump();
    break;
  case ExpressionValueType::ModuleValue:
    expression_value_result_.module->dump();
    break;
  }
}

std::unique_ptr<llvm::Value> ExpressionValue::value() {
  return std::move(expression_value_result_.value);
}
