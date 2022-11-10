COMMON_LIB:=../../utils
FILE_LIB:=$(COMMON_LIB)/fileReader/build
BOOT_LIB:=$(COMMON_LIB)/bootCode/build
SOURCE_FILE:=$(shell find -type f | \
	grep -E '*.c$$' | \
	sed -r 's/\./build/' | \
	sed -r 's/\.c/\.o/')
BIN:=build/day09.out

.DEFAULT_GOAL:=$(BIN)

build/:
	@mkdir build

build/%.o: %.c | build/
	@gcc -g -c -o $@ $<

clean:
	@rm -rf build/


$(BIN): $(SOURCE_FILE) | build/
	@gcc -o $@ $(SOURCE_FILE) \

debugger: $(BIN)
	@gdb $< 389125467

test: $(BIN)
	@$(BIN) 389125467

vtest: $(BIN)
	valgrind --leak-check=yes $(BIN) 389125467

run: $(BIN)
	@$(BIN) 253149867

vrun: $(BIN)
	valgrind --leak-check=yes $(BIN) 253149867

