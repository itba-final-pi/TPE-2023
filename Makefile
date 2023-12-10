SHELL := /bin/bash

COMPILER = gcc
FLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -D_XOPEN_SOURCE -D_GNU_SOURCE -D__USE_XOPEN
HEADERS = -Iheaders -ICTable
LINKER_FLAGS = -fsanitize=address
TEST_FLAGS = -DDEBUG_RUN_TESTS -g

# https://www.gnu.org/software/make/manual/html_node/Text-Functions.html
SOURCES := $(wildcard src/*.c helpers/*.c front/*.c)
OBJECTS := $(SOURCES:%.c=%.o)

# Allows defining the city when calling make
ifneq ($(CITY),)
	FLAGS += -D$(CITY)

# Target is New York City binary
	ifeq ($(CITY),NYC)
		NAME = bikeSharingNYC
	endif

# Target is Montreal
	ifeq ($(CITY),MON)
		NAME = bikeSharingMON
	endif

endif

# Compiles main.c file separately
main.o: main.c
	$(COMPILER) $(FLAGS) $(HEADERS) -c main.c -o main.o

# Compiles each src/*.c object into a .o file
$(OBJECTS): %.o : %.c
	$(COMPILER) $(FLAGS) $(HEADERS) -c $< -o $@

# Compile CTable separetely, as -Wextra -Werror fail compilation on a signed vs unsigned int comparison
# And we should **NOT** modify the CTable library. So in order for it to be compiled to an object and linked together,
# It needs to be treated separetly
./CTable/htmlTable.o:
	$(COMPILER) $(HEADERS) -Wall -pedantic -std=c99 -c ./CTable/htmlTable.c -o ./CTable/htmlTable.o

# Compiles and links specified test file
# make test file=./path/to/file.c (builds and runs specified file)
test: ./CTable/htmlTable.o
	$(COMPILER) $(FLAGS) $(LINKER_FLAGS) $(TEST_FLAGS) $(HEADERS) -Itests $(file) $(SOURCES) ./CTable/htmlTable.o -o ./tests/test.out

# Build and link together all sources (NOT THE TESTS)
.PHONY: all
all: main.o $(OBJECTS) ./CTable/htmlTable.o
	$(COMPILER) $(LINKER_FLAGS) $^ -o $(NAME)
	make clean

# Cleans out all object and binary files built
.PHONY: clean
clean:
	@find . -type f -name '*.o' -delete
	@find . -type f -name '*.out' -delete
	@find . -type d -name '*.out.dSYM' -exec rm -r {} +
