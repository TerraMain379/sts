# compiler
MAKE = make
MAKEFILE = Makefile
CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wcomment

# output
BIN_TARGET = main.bin
TEST_TARGET = tests.bin

# dirs
SOURCE_DIR = src
TEST_DIR = tests
TEST_UNITY_DIR = $(TEST_DIR)/unity
OBJ_DIR = build/o
PREPROCESSOR_DIR = build/pp

# build params (default)
TRANSFORM_FILES_TYPE = o
TRANSFORM_FILES_OPERATION = c


# sources directories
INCLUDE_DIRS = \
	src \
	src/collections \
	src/collections/gmap \
	src/collections/gmaps \
	src/collections/glist \
	src/collections/glists \
	src/errors \
	src/iter \
	src/memutils \
	src/strings \
	src/sts \
	src/sts/metaparser \
	src/sts/contentparser \

SRC_DIRS = $(INCLUDE_DIRS) src/sts/metaparser/metaparsermodules
TESTS_INCLUDE_DIRS = \
	tests \
	tests/unity \
	tests/collections \
	tests/collections/glist \
	tests/collections/glist/tgen \
	tests/collections/gmap \
	tests/collections/gmap/tgen \

TESTS_SRC_DIRS = $(TESTS_INCLUDE_DIRS)

# Generate include paths from source directories
INCLUDES = $(addprefix -I,$(INCLUDE_DIRS)) $(addprefix -I,$(TESTS_INCLUDE_DIRS))

# Find all .c/.h files in all directories
HEADERS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.h))
SOURCES = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.c))
SOURCES := $(filter-out %main.c, $(SOURCES))

TEST_HEADERS = $(foreach dir,$(TESTS_SRC_DIRS),$(wildcard $(dir)/*.h))
TEST_SOURCES = $(foreach dir,$(TESTS_SRC_DIRS),$(wildcard $(dir)/*.c))

MAIN_SOURCES = src/main.c

# Generate list of object files in o/ directory
TRANSFORM_FILES = $(SOURCES:%.c=$(OBJ_DIR)/%.$(TRANSFORM_FILES_TYPE))

TRANSFORM_TEST_FILES = $(TRANSFORM_FILES) \
	$(TEST_SOURCES:%.c=$(OBJ_DIR)/%.$(TRANSFORM_FILES_TYPE))
TRANSFORM_MAIN_FILES = $(TRANSFORM_FILES) \
	$(MAIN_SOURCES:%.c=$(OBJ_DIR)/%.$(TRANSFORM_FILES_TYPE))


 

# Create directories
$(OBJ_DIR) $(PREPROCESSOR_DIR):
	mkdir -p $@

# Rule for compiling .c files TRANSFORM files in o/ directory
$(OBJ_DIR)/%.$(TRANSFORM_FILES_TYPE): %.c $(HEADERS) | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -$(TRANSFORM_FILES_OPERATION) $< -o $@

# Rule for compiling test files
$(TEST_DIR)/%.$(TRANSFORM_FILES_TYPE): %.c @(TEST_HEADERS) | $(TEST_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -$(TRANSFORM_FILES_OPERATION) $< -o $@


# Clean
clean:
	rm -f $(TRANSFORM_TEST_FILES) $(BIN_TARGET) $(TEST_TARGET)
	rm -rf $(OBJ_DIR)


# tasks for build
MAKE_TRANFORM_MAIN_FILES: $(TRANSFORM_MAIN_FILES)
MAKE_TRANFORM_TEST_FILES: $(TRANSFORM_TEST_FILES)

MAKE_BIN_BY_TRANSFORM_MAIN_FILES: $(TRANSFORM_MAIN_FILES)
	$(CC) $(TRANSFORM_MAIN_FILES) -o $(BIN_TARGET)
MAKE_BIN_BY_TRANSFORM_TEST_FILES: $(TRANSFORM_TEST_FILES)
	$(CC) $(TRANSFORM_TEST_FILES) -o $(TEST_TARGET)

# tasks after build
SED_ENTERS_FOR_DOT_I_FILES: $(TRANSFORM_TEST_FILES)
	for file in $(TRANSFORM_TEST_FILES); do \
		sed -i 's/;\([^\n]\)/;\n\1\1/g' $$file; \
	done


# make links
build_bin:
	$(MAKE) --file=$(MAKEFILE) clean MAKE_TRANFORM_MAIN_FILES MAKE_BIN_BY_TRANSFORM_MAIN_FILES
gdb_bin:
	$(MAKE) --file=$(MAKEFILE) CFLAGS="$(CFLAGS) -g -DDEBUG" clean MAKE_TRANFORM_MAIN_FILES MAKE_BIN_BY_TRANSFORM_MAIN_FILES
build_test:
	$(MAKE) --file=$(MAKEFILE) clean MAKE_TRANFORM_TEST_FILES MAKE_BIN_BY_TRANSFORM_TEST_FILES
gdb_tests:
	$(MAKE) --file=$(MAKEFILE) CFLAGS="$(CFLAGS) -g -DDEBUG" clean MAKE_TRANFORM_TEST_FILES MAKE_BIN_BY_TRANSFORM_TEST_FILES

build_preprocessor:
	$(MAKE) --file=$(MAKEFILE) TRANSFORM_FILES_OPERATION=E TRANSFORM_FILES_TYPE=i \
		clean MAKE_TRANFORM_MAIN_FILES SED_ENTERS_FOR_DOT_I_FILES
build_test_preprocessor:
	$(MAKE) --file=$(MAKEFILE) TRANSFORM_FILES_OPERATION=E TRANSFORM_FILES_TYPE=i \
		clean MAKE_TRANFORM_TEST_FILES SED_ENTERS_FOR_DOT_I_FILES

# tasks
test: build_test
	@printf '\n\n\n'
	@./$(TEST_TARGET)

run: build_bin
	@./$(BIN_TARGET)

tokei:
	@echo '### SRC ###'
	@tokei ./src --exclude='*/_sts'
	@echo
	@echo '### TESTS ###'
	@tokei ./tests --exclude='*/unity'
	@echo
	@echo '### ALL ###'
	@tokei . --exclude='*/_sts' --exclude='*/unity'

.PHONY: MAKE_PREPROCESSOR
