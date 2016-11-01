################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/ast/add_node.cc \
../src/ast/call_node.cc \
../src/ast/constant_node.cc \
../src/ast/function_node.cc \
../src/ast/module_node.cc \
../src/ast/multiply_node.cc \
../src/ast/value_node.cc 

BCS += \
./src/ast/add_node.bc \
./src/ast/call_node.bc \
./src/ast/constant_node.bc \
./src/ast/function_node.bc \
./src/ast/module_node.bc \
./src/ast/multiply_node.bc \
./src/ast/value_node.bc 

CC_DEPS += \
./src/ast/add_node.d \
./src/ast/call_node.d \
./src/ast/constant_node.d \
./src/ast/function_node.d \
./src/ast/module_node.d \
./src/ast/multiply_node.d \
./src/ast/value_node.d 


# Each subdirectory must supply rules for building sources it contributes
src/ast/%.bc: ../src/ast/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: LLVM Clang++'
	clang++ -I/usr/local/Cellar/llvm/HEAD-d9176f9/include -O2 -emit-llvm -g -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


