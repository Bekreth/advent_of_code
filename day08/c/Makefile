COMMON_LIB:=../../utils
FILE_LIB:=$(COMMON_LIB)/fileReader/build
BOOT_LIB:=$(COMMON_LIB)/bootCode/build
SOURCE_FILE:=$(shell find -type f | \
	grep -E '*.c$$' | \
	sed -r 's/\./build/' | \
	sed -r 's/\.c/\.o/')

.DEFAULT_GOAL:=build/day08.out

build/:
	@mkdir build

build/%.o: %.c | build/
	@gcc -g -c -o $@ $<

clean:
	@rm -rf build/


build/day08.out: $(SOURCE_FILE) | build/
	@gcc -o $@ $(SOURCE_FILE) \
	$(FILE_LIB)/doubleBufferFileReader.o \
	$(FILE_LIB)/singleLineRecordProcessor.o \
	$(BOOT_LIB)/bootCode.o

debugger: build/day08.out
	@gdb $< 

test: build/day08.out
	@./build/day08.out ../input/sample.txt

run: build/day08.out
	@./build/day08.out ../input/data.txt
