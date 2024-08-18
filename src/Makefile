# Compiler and flags
CXX = g++  # Use g++ for C++ files
CC = gcc   # Use gcc for C files
CFLAGS = -std=c11 -Wall -Wextra -pedantic -Werror -g
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -Werror -g

# Directories
SRC_DIR = .
S21_MATRIX_DIR = s21_matrix
TEST_DIR = tests
BUILD_DIR = ../build
LIB_DIR = $(BUILD_DIR)/lib
OBJ_DIR = $(BUILD_DIR)/obj/src
S21_MATRIX_OBJ_DIR = $(BUILD_DIR)/obj/s21_matrix
TEST_OBJ_DIR = $(BUILD_DIR)/obj/tests

# Files and targets
LIB_TARGET = $(LIB_DIR)/s21_matrix_oop.a
CPP_SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
C_SOURCES = $(wildcard $(S21_MATRIX_DIR)/*.c)
CPP_OBJECTS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(CPP_SOURCES))
C_OBJECTS = $(patsubst $(S21_MATRIX_DIR)/%.c, $(S21_MATRIX_OBJ_DIR)/%.o, $(C_SOURCES))
OBJECTS = $(CPP_OBJECTS) $(C_OBJECTS)
TEST_SOURCES = $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.cpp, $(TEST_OBJ_DIR)/%.o, $(TEST_SOURCES))
TEST_TARGET = $(BUILD_DIR)/test_executable

# Google Test settings
GTEST_DIR = /path/to/gtest
GTEST_LIBS = -L$(GTEST_DIR)/lib -lgtest -lgtest_main -lpthread

# Phony targets
.PHONY: all clean test format fix s21_matrix_oop.a gcov_flag gcov_report

all: fix s21_matrix_oop.a

s21_matrix_oop.a: $(LIB_TARGET)

# Rule for creating the library
$(LIB_TARGET): $(CPP_OBJECTS) $(C_OBJECTS)
	mkdir -p $(LIB_DIR)
	ar rcs $@ $(CPP_OBJECTS) $(C_OBJECTS)

# Rule for compiling C++ source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule for compiling C source files
$(S21_MATRIX_OBJ_DIR)/%.o: $(S21_MATRIX_DIR)/%.c
	mkdir -p $(S21_MATRIX_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule for building tests
test: $(TEST_TARGET)
	$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(LIB_TARGET)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $(TEST_OBJECTS) $(LIB_TARGET) $(GTEST_LIBS) -lm

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp
	mkdir -p $(TEST_OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(GTEST_DIR)/include -I$(SRC_DIR) -I$(S21_MATRIX_DIR) -c $< -o $@

gcov_flag:
	$(eval CXXFLAGS += --coverage)
gcov_report: fix clean gcov_flag test
	mkdir -p report
	lcov --capture --directory $(BUILD_DIR)/obj/src/ --output-file coverage.info
	genhtml coverage.info --output-directory report
	rm -rf $(BUILD_DIR)/obj/src/*.gcno
	rm -rf $(BUILD_DIR)/obj/src/*.gcda
	rm -rf $(BUILD_DIR)/obj/src/*.gcov
	rm -rf $(BUILD_DIR)/obj/tests/*.gcno
	rm -rf $(BUILD_DIR)/obj/tests/*.gcda
	rm -rf $(BUILD_DIR)/obj/tests/*.gcov
	rm -rf coverage.info
	open report/index.html

# clang-format
format:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -n *.cpp *.hpp
	clang-format -n tests/*.cpp
	clang-format -n s21_matrix/*.c s21_matrix/*.h
	rm -rf .clang-format
fix:
	cp ../materials/linters/.clang-format ../src/.clang-format
	clang-format -i *.cpp *.hpp
	clang-format -i tests/*.cpp
	clang-format -i s21_matrix/*.c s21_matrix/*.h
	rm -rf .clang-format

# Rule for cleaning up
clean:
	rm -rf $(BUILD_DIR)/* report