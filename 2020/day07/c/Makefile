COMMON_LIB:=../../utils/fileReader/build
SOURCE_FILE:=$(shell find -type f | \
	grep -E '*.c$$' | \
	sed -r 's/\./build/' | \
	sed -r 's/\.c/\.o/')

.DEFAULT_GOAL:=build/day07.out

build/:
	@mkdir build

build/%.o: %.c | build/
	@gcc -g -c -o $@ $<

clean:
	@rm -rf build/


build/day07.out: $(SOURCE_FILE) | build/
	@gcc -o $@ $(SOURCE_FILE) \
	$(COMMON_LIB)/doubleBufferFileReader.o \
	$(COMMON_LIB)/singleLineRecordProcessor.o 

debugger: build/day07.out
	@gdb $< 

test: build/day07.out
	@./build/day07.out ../input/sample.txt

run: build/day07.out
	@./build/day07.out ../input/data.txt
