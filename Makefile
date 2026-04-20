# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -pedantic

# Директории
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj
TEST_DIR = test

EXAMPLE_TARTGET = $(BIN_DIR)/main
TEST_TARGET = $(BIN_DIR)/test

$(OBJ_DIR) $(BIN_DIR):
	mkdir -p $@

test: test.o vector.o

example:

valgrind:

clean:
	rm -rf $(BIN_DIR)/*
	rm -rf $(OBJ_DIR)/*

help:
	@echo "Доступные цели:"
	@echo "  test       - собрать и запустить тесты"
	@echo "  valgrind   - проверить тесты на утечку памяти"
	@echo "  example    - собрать и запустить пример"
	@echo "  clean      - удалить bin/* и obj/*"
