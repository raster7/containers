TEST_SRC := tests/s21_test_containers.cpp
LIB_SRC_DIR := lib_containers/

CC := g++
CFLAGS = -Wall -Werror -Wextra -std=c++17
TFLAG := -lgtest -lpthread

DATE := $(shell date)
OS := $(shell uname -s)

all: clean test

test:
	$(CC) -o test_containers $(TEST_SRC) $(CFLAGS) $(TFLAG)
	./test_containers

clean:
	rm -rf *.o tests/*.o  \
	./test_containers     \
	./main                \
	./a.out	              \
	.clang-format

check: check_clang check_leaks

check_clang:
	@cp ../materials/linters/.clang-format ./.clang-format
	@clang-format -n *.h tests/*
	@clang-format -n $(LIB_SRC_DIR)/vector/* $(LIB_SRC_DIR)/list/* $(LIB_SRC_DIR)/stack/*
	@clang-format -i *.h tests/* $(LIB_SRC_DIR)/vector/* $(LIB_SRC_DIR)/list/* $(LIB_SRC_DIR)/stack/*
	@rm .clang-format

check_leaks: test
ifeq ($(OS), Linux)
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all -s ./test_containers
else
	leaks -atExit -- ./test_containers | grep LEAK:
endif

push:
	git add .
	git commit -m "$(DATE)"
	git push

.PHONY: all             \
		clean           \
		test            \
		check
