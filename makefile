CC = gcc
CFLAGS = -Wall -pedantic -fsanitize=address

BIN = bin

SPARSE_PROJECT = SparseMatrix
SPARSE_TEST_RUNNER = SparseMatrixTest

INCLUDE_DIR = include
SRC_DIR = src
SPARSE_DIR = $(SRC_DIR)/$(SPARSE_PROJECT)
TEST_DIR = test
SPARSE_TEST_DIR = $(TEST_DIR)/$(SPARSE_PROJECT)

INCLUDES = $(addprefix -I, $(shell find $(INCLUDE_DIR) -type d))
TEST_INCLUDE = -I$(TEST_DIR)

SRC = $(shell find $(SRC_DIR) -maxdepth 1 -type f -name "*.c")
SPARSE_SRC = $(shell find $(SPARSE_DIR) -type f -name "*.c")
TEST_SRC = $(shell find $(TEST_DIR) -maxdepth 1 -type f -name "*.c")
SPARSE_TEST_SRC = $(shell find $(SPARSE_TEST_DIR) -type f -name "*.c")

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN)/src/%.o, $(SRC))
SPARSE_OBJS = $(patsubst $(SPARSE_DIR)/%.c, $(BIN)/sparse/%.o, $(SPARSE_SRC))

# Necessary to build test runners because of multiple "main" definition
# Dirty solution, must be cleaned 
SPARSE_OBJ = $(BIN)/sparse/SparseMatrix.o

TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(BIN)/test/%.o, $(TEST_SRC))
SPARSE_TEST_OBJS = $(patsubst $(SPARSE_TEST_DIR)/%.c, $(BIN)/sparsetest/%.o, $(SPARSE_TEST_SRC))

.PHONY: all sparse sparse-test clean

all: sparse sparse-test

sparse: $(BIN)/$(SPARSE_PROJECT)

sparse-test: $(BIN)/$(SPARSE_TEST_RUNNER)

# Link SparseMatrix
$(BIN)/$(SPARSE_PROJECT): $(OBJS) $(SPARSE_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Build general use objects (gui, utils, etc.)
$(BIN)/src/%.o: $(SRC_DIR)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build SparseMatrix objects
$(BIN)/sparse/%.o: $(SPARSE_DIR)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link SparseMatrix test runner
$(BIN)/$(SPARSE_TEST_RUNNER): $(TEST_OBJS) $(SPARSE_TEST_OBJS) $(SPARSE_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Build Unity C test framework
$(BIN)/test/%.o: $(TEST_DIR)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(TEST_INCLUDE) -c $< -o $@

# Build SparseMatrix test runner
$(BIN)/sparsetest/%.o: $(SPARSE_TEST_DIR)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_INCLUDE) -c $< -o $@

$(BIN):
	mkdir -p $(BIN)/src $(BIN)/sparse $(BIN)/test $(BIN)/sparsetest

clean:
	rm -rf $(BIN)