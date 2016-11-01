################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/builder_adaptor.cc 

BCS += \
./src/builder_adaptor.bc 

CC_DEPS += \
./src/builder_adaptor.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.bc: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: LLVM Clang++'
	clang++ -I/usr/local/Cellar/llvm/HEAD-d9176f9/include -O2 -emit-llvm -g -Wall -c -fmessage-length=0 -std=c++0x -MMD -MP -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


