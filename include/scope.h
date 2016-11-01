#ifndef CANOE_SCOPE_H_
#define CANOE_SCOPE_H_

class Module;

struct Scope {
  Module module;
  std::map<std::string, Value *> named_values;
  std::map<std::string, Function *> named_functions;
};

#endif
