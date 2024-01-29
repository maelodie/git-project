PROGRAMS=main
CC=gcc
CFLAGS=-Wall -Werror -I./include
SRC_DIR=./src
OBJ_DIR=./obj
BIN_DIR=./bin

# source files
SRC_FILES=$(wildcard $(SRC_DIR)/*.c)

# object files 
OBJ_FILES=$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# final executable
EXECUTABLE=$(BIN_DIR)/myGit

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)/* $(BIN_DIR)/*