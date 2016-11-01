#ifndef CANOE_HEADING_H_
#define CANOE_HEADING_H_

#define YY_NO_UNPUT

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include "ast/node.h"
#include "ast/function_node.h"
#include "ast/value_node.h"
#include "ast/call_node.h"
#include "ast/add_node.h"
#include "ast/multiply_node.h"
#include "ast/constant_node.h"
#include "ast/module_node.h"

#include "llvm/IR/Module.h"

#include "scope.h"
#include "builder_adaptor.h"

using namespace std;

template<class T>
class SizedArray {
public:
  int size = 0;
  T array[100];

  void push(T t) {
    array[size++] = t;
  }
};

typedef SizedArray<Node*> SizedNodeArray;

#endif
