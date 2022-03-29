APP = chessviz
LIB = libchessviz

SRC = src
OBJ = obj
BIN = bin

SRC_EXT = c
OBJ_EXT = o
LIB_EXT = a

APP_SRC = $(shell find $(SRC)/$(APP) -name "*.$(SRC_EXT)")
APP_OBJ = $(APP_SRC:$(SRC)/%.$(SRC_EXT)=$(OBJ)/$(SRC)/%.$(OBJ_EXT))
APP_BIN = $(BIN)/$(APP)

LIB_SRC = $(shell find $(SRC)/$(LIB) -name "*.$(SRC_EXT)")
LIB_OBJ = $(LIB_SRC:$(SRC)/%.$(SRC_EXT)=$(OBJ)/$(SRC)/%.$(OBJ_EXT))
LIB_PATH = $(OBJ)/$(SRC)/$(LIB)/$(LIB).$(LIB_EXT)

DEPS = $(APP_OBJ:.$(OBJ_EXT)=.d) $(LIB_OBJ:.$(OBJ_EXT)=.d)

-include $(DEPS)

CFLAGS = -Wall -Werror
CPPFLAGS = -I $(SRC) -MMD

.PHONY: all clean run

all: $(APP_BIN)

$(APP_BIN): $(APP_OBJ) $(LIB_PATH)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

$(LIB_PATH): $(LIB_OBJ)
	$(AR) rcs $@ $^

$(OBJ)/%.$(OBJ_EXT): %.$(SRC_EXT)
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

clean:
	$(RM) $(APP_BIN) $(LIB_PATH) $(APP_OBJ) $(LIB_OBJ) $(DEPS)

run: $(APP_BIN)
	./$(APP_BIN)
