CC := gcc
CFLAGS := -Wall -Wextra -g
INCLUDES := -I.
LIBS := -luser32 -lws2_32
DEFINES :=

MKDIR := mkdir
RMDIR := rmdir /s /q

RES_DIR := res
SRC_DIR := src
OBJ_DIR := obj
BUILD_DIR := bin

SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
EXEC := sxserver.exe

### ALL
all: $(BUILD_DIR)/$(EXEC)

clean: clnexec

## EXECUTABLE
$(BUILD_DIR)/$(EXEC): $(OBJS) | $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(DEFINES) $(INCLUDES)

$(BUILD_DIR) $(OBJ_DIR):
	$(MKDIR) $@

run:
	$(BUILD_DIR)/$(EXEC)

clnexec:
	$(RMDIR) $(BUILD_DIR) $(OBJ_DIR)
