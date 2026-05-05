CC      := gcc
CFLAGS  := -Wall -pedantic -fsanitize=address

BIN         := bin
INCLUDE_DIR := include
SRC_DIR     := src
TEST_DIR    := test

PROJECTS := SparseMatrix PatientIndexer

SparseMatrix_ALIAS  := sparse
PatientIndexer_ALIAS := indexer

INCLUDES     := $(addprefix -I, $(shell find $(INCLUDE_DIR) -type d))
TEST_INCLUDE := -I$(TEST_DIR)

COMMON_SRC  := $(shell find $(SRC_DIR) -maxdepth 1 -type f -name "*.c")
COMMON_OBJS := $(patsubst $(SRC_DIR)/%.c, $(BIN)/src/%.o, $(COMMON_SRC))

TEST_SRC  := $(shell find $(TEST_DIR) -maxdepth 1 -type f -name "*.c")
TEST_OBJS := $(patsubst $(TEST_DIR)/%.c, $(BIN)/test/%.o, $(TEST_SRC))

UTILS_TEST_SRC  := $(shell find $(TEST_DIR)/Utils -type f -name "*.c")
UTILS_TEST_OBJS := $(patsubst $(TEST_DIR)/Utils/%.c, $(BIN)/utilstest/%.o, $(UTILS_TEST_SRC))


define project_vars
  # Source directories
  $(1)_SRC_DIR       := $(SRC_DIR)/$(1)
  $(1)_TEST_DIR      := $(TEST_DIR)/$(1)

  # Output directories
  $(1)_OBJ_DIR       := $(BIN)/$($(1)_ALIAS)
  $(1)_TEST_OBJ_DIR  := $(BIN)/$($(1)_ALIAS)test

  # Sources
  $(1)_SRC           := $$(shell find $$($(1)_SRC_DIR)  -type f -name "*.c")
  $(1)_TEST_SRC      := $$(shell find $$($(1)_TEST_DIR) -type f -name "*.c")

  # Objects
  $(1)_OBJS          := $$(patsubst $$($(1)_SRC_DIR)/%.c,  $$($(1)_OBJ_DIR)/%.o,      $$($(1)_SRC))
  $(1)_TEST_OBJS     := $$(patsubst $$($(1)_TEST_DIR)/%.c, $$($(1)_TEST_OBJ_DIR)/%.o, $$($(1)_TEST_SRC))

  # The single object needed when linking the test runner (avoids duplicate main)
  $(1)_MAIN_OBJ      := $$($(1)_OBJ_DIR)/$(1).o
endef

$(foreach P, $(PROJECTS), $(eval $(call project_vars,$(P))))

.PHONY: all clean help $(foreach P,$(PROJECTS), \
          $($(P)_ALIAS) $($(P)_ALIAS)-test) utils-test

help: ## Show this help.
	@sed -ne '/@sed/!s/## //p' $(MAKEFILE_LIST)

all: $(foreach P,$(PROJECTS), $($(P)_ALIAS) $($(P)_ALIAS)-test) utils-test ## Build everything.

utils-test: $(BIN)/UtilsTest  ## Build the Utils test runner.

define phony_targets
$($(1)_ALIAS): $(BIN)/$(1)             ## Build the $(1) project.
$($(1)_ALIAS)-test: $(BIN)/$(1)Test    ## Build the $(1) test runner.
endef

$(foreach P,$(PROJECTS), $(eval $(call phony_targets,$(P))))

define link_rules

$(BIN)/$(1): $(COMMON_OBJS) $$($(1)_OBJS)
	$(CC) $(CFLAGS) $$^ -o $$@


$(BIN)/$(1)Test: $(TEST_OBJS) $$($(1)_TEST_OBJS) $$($(1)_MAIN_OBJ) $(COMMON_OBJS)
	$(CC) $(CFLAGS) $$^ -o $$@
endef

$(foreach P,$(PROJECTS), $(eval $(call link_rules,$(P))))


$(BIN)/src/%.o: $(SRC_DIR)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Unity objects
$(BIN)/test/%.o: $(TEST_DIR)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(TEST_INCLUDE) -c $< -o $@


define compile_rules
$(BIN)/$($(1)_ALIAS)/%.o: $(SRC_DIR)/$(1)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) -c $$< -o $$@

$(BIN)/$($(1)_ALIAS)test/%.o: $(TEST_DIR)/$(1)/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_INCLUDE) -c $$< -o $$@
endef

$(foreach P,$(PROJECTS), $(eval $(call compile_rules,$(P))))

$(BIN)/utilstest/%.o: $(TEST_DIR)/Utils/%.c | $(BIN)
	$(CC) $(CFLAGS) $(INCLUDES) $(TEST_INCLUDE) -c $< -o $@

$(BIN)/UtilsTest: $(TEST_OBJS) $(UTILS_TEST_OBJS) $(COMMON_OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(BIN):
	mkdir -p $(BIN)/src $(BIN)/test $(BIN)/utilstest \
	  $(foreach P,$(PROJECTS), $(BIN)/$($(P)_ALIAS) $(BIN)/$($(P)_ALIAS)test)


clean: ## Remove all built files, including binaries.
	rm -rf $(BIN)