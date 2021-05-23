bins := $(patsubst src/%.c,bin/%,$(wildcard src/*.c))

all: ${bins}

bin/% : src/%.c | bin
	gcc $^ -o $@

bin :
	mkdir -p $@
