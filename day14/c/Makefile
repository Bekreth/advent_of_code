COMMON_LIB:=../../utils
FILE_LIB:=$(COMMON_LIB)/fileReader/build
BOOT_LIB:=$(COMMON_LIB)/bootCode/build
SOURCE_FILE:=$(shell find -type f | \
	grep -E '*.c$$' | \
	sed -r 's/\./build/' | \
	sed -r 's/\.c/\.o/')
BIN:=build/day14.out

.DEFAULT_GOAL:=$(BIN)

build/:
	@mkdir build

build/%.o: %.c | build/
	@gcc -g -c -o $@ $<

clean:
	@rm -rf build/


$(BIN): $(SOURCE_FILE) | build/
	@gcc -o $@ $(SOURCE_FILE) \
	$(FILE_LIB)/doubleBufferFileReader.o \
	$(FILE_LIB)/singleLineRecordProcessor.o

debugger: $(BIN)
	@gdb $< 

test: $(BIN)
	@$(BIN) ../input/sample.txt 5

test2: $(BIN)
	@$(BIN) ../input/sample2.txt 5

vtest: $(BIN)
	valgrind --leak-check=yes $(BIN) ../input/sample.txt 5

run: $(BIN)
	@$(BIN) ../input/data.txt 10

vrun: $(BIN)
	valgrind --leak-check=yes $(BIN) ../input/data.txt 25

