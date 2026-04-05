CC = gcc
FLAGS = -Wall -pedantic

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

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN)/%.o, $(SRC))
SPARSE_OBJS = $(patsubst $(SPARSE_DIR)/%.c, $(BIN)/%.o, $(SPARSE_SRC))
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(BIN)/%.o, $(TEST_SRC))
SPARSE_TEST_OBJS = $(patsubst $(SPARSE_TEST_DIR)/%.c, $(BIN)/%.o, $(SPARSE_TEST_SRC))

.PHONY: all sparse sparse-test clean

all: sparse sparse-test

sparse: $(BIN)/$(SPARSE_PROJECT)

sparse-test: $(BIN)/$(SPARSE_TEST_RUNNER)

# Link SparseMatrix
$(BIN)/$(SPARSE_PROJECT): $(OBJS) $(SPARSE_OBJS)
	$(CC) $(FLAGS) $^ -o $@

# Build general use objects (gui, utils, etc.)
$(BIN)/%.o: $(SRC_DIR)/%.c | $(BIN)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

# Build SparseMatrix objects
$(BIN)/%.o: $(SPARSE_DIR)/%.c | $(BIN)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

# Link SparseMatrix test runner
$(BIN)/$(SPARSE_TEST_RUNNER): $(TEST_OBJS) $(SPARSE_TEST_OBJS) $(SPARSE_OBJS) $(OBJS)
	$(CC) $(FLAGS) $^ -o $@

# Build Unity C test framework
$(BIN)/%.o: $(TEST_DIR)/%.c | $(BIN)
	$(CC) $(FLAGS) $(TEST_INCLUDE) -c $< -o $@

# Build SparseMatrix test runner
$(BIN)/%.o: $(SPARSE_TEST_DIR)/%.c | $(BIN)
	$(CC) $(FLAGS) $(INCLUDES) $(TEST_INCLUDE) -c $< -o $@

$(BIN):
	mkdir -p $(BIN)

clean:
	rm -rf $(BIN)