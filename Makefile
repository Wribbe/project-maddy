bins := $(patsubst src/%.c,bin/%,$(wildcard src/*.c))
FLAGS := -Wall --pedantic -I. -g
LOCAL_LIBS := $(wildcard lib/*.c)

all: ${bins}

test: bin/test
	valgrind ./bin/test

bin/% : Makefile src/%.c ${LOCAL_LIBS} | bin
	gcc $(filter %.c,$^) -o $@ ${FLAGS}

bin :
	mkdir -p $@
