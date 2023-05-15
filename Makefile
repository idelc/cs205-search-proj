CC=g++
BUILDDIR ?= output

TARGET := ${BUILDDIR}/bw_puzzle
SRC := $(wildcard $src/*.c)

COMMON_FLAGS := -Wall -Wextra -Werror

.PHONY: all clean test

all:
	$(CC)  -o bw_puzzle src/main.cpp

clean:
	$(RM) -r Trace.txt bw_puzzle

test: all
	./bw_puzzle