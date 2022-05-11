APP = chessviz
LIB = libchessviz

SRC = src
OBJ = obj
BIN = bin
TEST = test

SRC_EXT = c
OBJ_EXT = o
LIB_EXT = a

APP_SRC = $(shell find $(SRC)/$(APP) -name "*.$(SRC_EXT)")
APP_OBJ = $(APP_SRC:$(SRC)/%.$(SRC_EXT)=$(OBJ)/$(SRC)/%.$(OBJ_EXT))
APP_BIN = $(BIN)/$(APP)

LIB_SRC = $(shell find $(SRC)/$(LIB) -name "*.$(SRC_EXT)")
LIB_OBJ = $(LIB_SRC:$(SRC)/%.$(SRC_EXT)=$(OBJ)/$(SRC)/%.$(OBJ_EXT))
LIB_PATH = $(OBJ)/$(SRC)/$(LIB)/$(LIB).$(LIB_EXT)

TEST_SRC = $(shell find $(TEST) -name "*.$(SRC_EXT)")
TEST_OBJ = $(TEST_SRC:$(TEST)/%.$(SRC_EXT)=$(OBJ)/$(TEST)/%.$(OBJ_EXT))
TEST_BIN = $(BIN)/$(APP)-$(TEST)

DEPS = $(APP_OBJ:.$(OBJ_EXT)=.d) $(LIB_OBJ:.$(OBJ_EXT)=.d) $(TEST_OBJ:.$(OBJ_EXT)=.d)

-include $(DEPS)

CFLAGS = -Wall -Werror
CPPFLAGS = -I $(SRC) -MMD
CPPFLAGS_TEST = -I $(SRC) -I thirdparty -MMD

.PHONY: all test clean run

all: $(APP_BIN)

$(APP_BIN): $(APP_OBJ) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(TEST_BIN): $(TEST_OBJ) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS_TEST) $^ -o $@

$(LIB_PATH): $(LIB_OBJ)
	$(AR) rcs $@ $^

# APP & LIB objects
$(OBJ)/$(SRC)/%.$(OBJ_EXT): $(SRC)/%.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

# TEST objects
$(OBJ)/$(TEST)/%.$(OBJ_EXT): $(TEST)/%.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS_TEST) $< -o $@

clean:
	$(RM) $(APP_BIN) $(LIB_PATH) $(TEST_BIN) $(APP_OBJ) $(LIB_OBJ) $(TEST_OBJ) $(DEPS)

test: $(TEST_BIN)
	./$(TEST_BIN)

run: $(APP_BIN)
	./$(APP_BIN)
