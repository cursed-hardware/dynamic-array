CC := gcc
CFLAGS := -Wall -Wextra -pedantic

SRC_DIR := src
BIN_DIR := bin

TARGET := vector

target:
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(TARGET) $(SRC_DIR)/vector.c

clean:
	rm -rf $(BIN_DIR)/*

run:
	exec $(BIN_DIR)/vector
