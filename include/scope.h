#ifndef CANOE_SCOPE_H_
#define CANOE_SCOPE_H_

#include <map>

namespace llvm {
class Argument;
class Function;
class Module;
}

struct Scope {
  // TODO: Make unique_ptr
  std::unique_ptr<llvm::Module> module;

  std::map<std::string, std::unique_ptr<llvm::Argument>> named_values;
  std::map<std::string, std::unique_ptr<llvm::Function>> named_functions;
};

#endif
