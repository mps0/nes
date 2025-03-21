# tool macros
CC := g++
CFLAGS := -pedantic -Wall -Wextra -g
COBJFLAGS := $(CFLAGS)
CXX_STANDRD := c++20

# path macros
BIN_PATH := bin
OBJ_PATH := $(BIN_PATH)/obj
SRC_PATH := src
TEST_PATH := test

# compile macros
TARGET_NAME := nes
TARGET := $(BIN_PATH)/$(TARGET_NAME)
TEST_TARGET := $(BIN_PATH)/test_$(TARGET_NAME)

MAIN := $(SRC_PATH)/main.cpp

# src files & obj files
SRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.cpp)))
OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

TEST_SRC := $(filter-out $(MAIN), $(SRC)) $(foreach x, $(TEST_PATH), $(wildcard $(addprefix $(x)/*,.cpp)))
TEST_OBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(TEST_SRC)))))

# deps
DEPS := $(OBJS:.o=.d)
TEST_DEPS := $(TEST_OBJS:.o=.d)

# compile_flags.txt includes
INC_DIRS := $(shell find $(SRC_PATH) -type d)
INC_FLAGS := $(addprefix -I, $(INC_DIRS))

CLANG_D_INCLUDES := $(addsuffix '\n', $(INC_FLAGS))

# clean files list
DISTCLEAN_LIST := $(OBJ) \
				  $(TEST_OBJ) \
				  $(DEPS) \
				  $(TEST_DEPS) \
				  compile_flags.txt
CLEAN_LIST := $(TARGET) \
			  $(TEST_TARGET) \
			  $(DISTCLEAN_LIST)


all: makedir $(TARGET)
# non-phony targets
$(TARGET): $(OBJ) compile_flags.txt
	$(CC) -o $@ $(OBJ) $(CFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(info Compiling: $<)
	$(CC) $(COBJFLAGS) -c $< -o $@

$(OBJ_PATH)/%.o: $(TEST_PATH)/%.cpp
	$(info Compiling: $<)
	$(CC) $(COBJFLAGS) -c $< -o $@

compile_flags.txt:
	@echo -e -std=$(CXX_STANDRD)'\n'-xc++'\n'$(CLANG_D_INCLUDES) > $@

$(TEST_TARGET): $(TEST_OBJ)
	$(CC) -o $@ $(TEST_OBJ) $(CFLAGS)


# phony rules
.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)

.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: test
test: $(TEST_TARGET)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)

.PHONY: distclean
distclean:
	@echo CLEAN $(DISTCLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)

include $(DEPS)
