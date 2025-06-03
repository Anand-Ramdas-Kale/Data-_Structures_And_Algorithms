# Makefile for fib-heap project

CC = gcc
CFLAGS = -ggdb -Wall -Wextra -O2 -I..
BUILD_DIR = ../build
SRC_DIR = ..
TEST_DIR = ../test-fib

OBJS = $(BUILD_DIR)/heap.o $(BUILD_DIR)/parser.o $(BUILD_DIR)/main.o
TARGET = $(BUILD_DIR)/main

all: $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/heap.o: $(SRC_DIR)/heap.c $(SRC_DIR)/heap.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/parser.o: $(TEST_DIR)/parser.c $(TEST_DIR)/parser.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/main.o: $(TEST_DIR)/main.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)/*

.PHONY: all clean
