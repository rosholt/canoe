#ifndef CANOE_EXPRESSION_VALUE_H_
#define CANOE_EXPRESSION_VALUE_H_

#include <memory>

namespace llvm {
class Value;
class Function;
class Module;
}

enum class ExpressionValueType {
  FunctionValue, ValueValue, ModuleValue
};

struct ExpressionValueResult {
  std::unique_ptr<llvm::Function> function;
  std::unique_ptr<llvm::Value> value;
  std::unique_ptr<llvm::Module> module;
};

class ExpressionValue {
private:
  ExpressionValueType expression_value_type_;
  ExpressionValueResult expression_value_result_;

public:
  ExpressionValue(std::unique_ptr<llvm::Function> function);
  ExpressionValue(std::unique_ptr<llvm::Value> value);
  ExpressionValue(std::unique_ptr<llvm::Module> module);

  void dump();
  std::unique_ptr<llvm::Value> value();
};

#endif
