SOURCE_FILE:=$(shell find -type f | \
	grep -E '*.c$$' | \
	sed -r 's/\./build/' | \
	sed -r 's/\.c/\.o/')
BIN:=build/day22.out

.DEFAULT_GOAL:=$(BIN)

build/:
	@mkdir build

build/%.o: %.c | build/
	@gcc -g -c -o $@ $<

clean:
	@rm -rf build/

test: $(SOURCE_FILE) | build/
	@gcc -o $(BIN) build/main.o build/deck_sample.o build/combat.o
	@$(BIN) 

run: $(SOURCE_FILE) | build/
	@gcc -o $(BIN) build/main.o build/deck_data.o build/combat.o
	@$(BIN) 

