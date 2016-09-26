#TODO: Include cppcheck and clang static analyzer


PROJECT_NAME=canoe

VPATH = src:build:src/ast:generated

.PRECIOUS: build generated generated/%.cc build/%.o generated/%.h bin/%

PARSER_OBJECT_FILE = build/parser.o
LEXER_OBJECT_FILE = build/lexer.o

SOURCE_FILE_DIRECTORIES = src src/ast
SOURCE_FILES = $(foreach dir, $(SOURCE_FILE_DIRECTORIES), $(wildcard $(dir)/*.cc))
OBJECT_FILES = $(PARSER_OBJECT_FILE) $(LEXER_OBJECT_FILE) $(SOURCE_FILES:src/%.cc=build/%.o)

CLANG = clang++
CFLAGS = -Wno-write-strings -std=c++11 -x c++ -Iinclude -I/usr/local/opt/llvm/include -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS -Wno-deprecated-register
LLVM_FLAGS = $(shell llvm-config --cxxflags --ldflags --system-libs --libs core) -ll


# Build executable
bin/$(PROJECT_NAME): $(OBJECT_FILES)
	mkdir -p $(dir $@)
	$(CLANG) $^ $(LLVM_FLAGS) -o $@

build/%.o: %.cc
	mkdir -p $(dir $@)
	$(CLANG) $(CFLAGS) -c $< -o $@

build/%.o: generated/%.cc
	mkdir -p $(dir $@)
	$(CLANG) $(CFLAGS) -c $< -o $@

generated/%.cc: %.lex
	mkdir -p $(dir $@)
	flex -o $@ $<

generated/%.cc generated/%.h: %.y
	mkdir -p $(dir $@)
	bison -d -o $@ $< && mv generated/$*.hh generated/$*.h

clean:
	rm -rf generated build bin
