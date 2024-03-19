CC=gcc
CFLAGS=-Wall -g
CINCLUDE=-I./include/
CFLAGS+=$(CINCLUDE)

BIN=storage
SRC=$(wildcard src/*.c)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $^ -o $@

.PHONY: clean
clean:
	rm -f $(BIN)
