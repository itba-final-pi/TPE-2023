SHELL := /bin/bash

COMPILER = gcc
FLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -D$(CITY)
LINKER_FLAGS = -fsanitize=address
TEST_FLAGS = -DDEBUG_RUN_TESTS

# https://www.gnu.org/software/make/manual/html_node/Text-Functions.html
SOURCES := $(wildcard src/*.c helpers/*.c)
OBJECTS := $(SOURCES:%.c=%.o)

# Compiles main.c file separately
main.o: main.c
	$(COMPILER) $(FLAGS) -c main.c -o main.o

# Compiles each src/*.c object into a .o file
$(OBJECTS): %.o : %.c
	$(COMPILER) $(FLAGS) -Iheaders -c $< -o $@

# Compiles and links specified test file
# make test file=./path/to/file.c (builds and runs specified file)
test:
	$(COMPILER) $(FLAGS) $(LINKER_FLAGS) $(TEST_FLAGS) -Iheaders -Itests $(file) $(SOURCES) -o ./tests/test.out

# Build and link together all sources (NOT THE TESTS)
.PHONY: all
all: main.o $(OBJECTS)
	$(COMPILER) $(LINKER_FLAGS) $^ -o Binary.out

# Debugging
.PHONY: print
print:
	@echo $(OBJECTS)
	@echo $(SOURCES)
	@echo $(TESTS)

# Cleans out all object and binary files built
.PHONY: clean
clean:
	@find . -type f -name '*.o' -delete
	@find . -type f -name '*.out' -delete
