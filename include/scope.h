#ifndef JUGGERNAUT_SCOPE_H_
#define JUGGERNAUT_SCOPE_H_

#include <map>

struct Scope {
  std::map<std::string, Value *> named_values;
};

#endif