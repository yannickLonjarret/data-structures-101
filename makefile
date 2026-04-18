CC = gcc
CFLAGS = -Wall -pedantic

BIN = bin

SPARSE_PROJECT = SparseMatrix
SPARSE_TEST_RUNNER = SparseMatrixTest

INDEXER_PROJECT = PatientIndexer
INDEXER_TEST_RUNNER = PatientIndexerTest

INCLUDE_DIR = include
SRC_DIR = src
SPARSE_DIR = $(SRC_DIR)/$(SPARSE_PROJECT)
INDEXER_DIR = $(SRC_DIR)/$(INDEXER_PROJECT)
TEST_DIR = test
SPARSE_TEST_DIR = $(TEST_DIR)/$(SPARSE_PROJECT)
INDEXER_TEST_DIR = $(TEST_DIR)/$(INDEXER_PROJECT)

INCLUDES = $(addprefix -I, $(shell find $(INCLUDE_DIR) -type d))
TEST_INCLUDE = -I$(TEST_DIR)

SRC = $(shell find $(SRC_DIR) -maxdepth 1 -type f -name "*.c")
SPARSE_SRC = $(shell find $(SPARSE_DIR) -type f -name "*.c")
INDEXER_SRC = $(shell find $(INDEXER_DIR) -type f -name "*.c")
TEST_SRC = $(shell find $(TEST_DIR) -maxdepth 1 -type f -name "*.c")
SPARSE_TEST_SRC = $(shell find $(SPARSE_TEST_DIR) -type f -name "*.c")
INDEXER_TEST_SRC = $(shell find $(INDEXER_TEST_DIR) -type f -name "*.c")

OBJS = $(patsubst $(SRC_DIR)/%.c, $(BIN)/src/%.o, $(SRC))
SPARSE_OBJS = $(patsubst $(SPARSE_DIR)/%.c, $(BIN)/sparse/%.o, $(SPARSE_SRC))
INDEXER_OBJS = $(patsubst $(INDEXER_DIR)/%.c, $(BIN)/indexer/%.o, $(INDEXER_SRC))

# Necessary to build test runners because of multiple "main" definition
SPARSE_OBJ = $(BIN)/sparse/SparseMatrix.o
INDEXER_OBJ = $(BIN)/indexer/PatientIndexer.o

TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(BIN)/test/%.o, $(TEST_SRC))
SPARSE_TEST_OBJS = $(patsubst $(SPARSE_TEST_DIR)/%.c, $(BIN)/sparsetest/%.o, $(SPARSE_TEST_SRC))
INDEXER_TEST_OBJS = $(patsubst $(INDEXER_TEST_DIR)/%.c, $(BIN)/indexertest/%.o, $(INDEXER_TEST_SRC))

.PHONY: all sparse sparse-test indexer indexer-test clean help

help: ## Show this help.
	@sed -ne '/@sed/!s/## //p' $(MAKEFILE_LIST)

all: sparse sparse-test indexer indexer-test ## Build everything.

sparse: $(BIN)/$(SPARSE_PROJECT) ## Build the SparseMatrix project.

sparse-test: $(BIN)/$(SPARSE_TEST_RUNNER) ## Build the SparseMatrix test runner.

indexer: $(BIN)/$(INDEXER_PROJECT) ## Build the PatientIndexer project.

indexer-test: $(BIN)/$(INDEXER_TEST_RUNNER) ## Build the PatientIndexer test runner.



# Link SparseMatrix
$(BIN)/$(SPARSE_PROJECT): $(OBJS) $(SPARSE_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Link PatientIndexer
$(BIN)/$(INDEXER_PROJECT): $(OBJS) $(INDEXER_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Build general use objects (gui, utils, etc.)
$(BIN)/src/%.o: $(SRC_DIR)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build SparseMatrix objects
$(BIN)/sparse/%.o: $(SPARSE_DIR)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Build PatientIndexer objects
$(BIN)/indexer/%.o: $(INDEXER_DIR)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Link SparseMatrix test runner
$(BIN)/$(SPARSE_TEST_RUNNER): $(TEST_OBJS) $(SPARSE_TEST_OBJS) $(SPARSE_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Link PatientIndexer test runner
$(BIN)/$(INDEXER_TEST_RUNNER): $(TEST_OBJS) $(INDEXER_TEST_OBJS) $(INDEXER_OBJ) $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Build Unity C test framework
$(BIN)/test/%.o: $(TEST_DIR)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(TEST_INCLUDE) -c $< -o $@

# Build SparseMatrix test runner
$(BIN)/sparsetest/%.o: $(SPARSE_TEST_DIR)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_INCLUDE) -c $< -o $@

# Build PatientIndexer test runner
$(BIN)/indexertest/%.o: $(INDEXER_TEST_DIR)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_INCLUDE) -c $< -o $@

$(BIN):
	mkdir -p $(BIN)/src $(BIN)/sparse $(BIN)/test $(BIN)/sparsetest $(BIN)/indexer $(BIN)/indexertest

clean: ## Remove all built file, including binaries.
	rm -rf $(BIN)