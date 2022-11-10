COMMON_LIB:=../../utils
FILE_LIB:=$(COMMON_LIB)/fileReader/build
BOOT_LIB:=$(COMMON_LIB)/bootCode/build
SOURCE_FILE:=$(shell find -type f | \
	grep -E '*.c$$' | \
	sed -r 's/\./build/' | \
	sed -r 's/\.c/\.o/')
BIN:=build/day19.out

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
	@$(BIN) 5 ../input/sample_rules.txt ../input/sample_data.txt

vtest: $(BIN)
	valgrind --leak-check=yes $(BIN) 5 ../input/sample_rules.txt ../input/sample_data.txt

run: $(BIN)
	@$(BIN) 5 ../input/data_rules.txt ../input/data_data.txt

vrun: $(BIN)
	valgrind --leak-check=yes $(BIN) 5 ../input/data_rules.txt ../input/data_data.txt

