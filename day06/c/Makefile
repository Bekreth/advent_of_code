COMMON_LIB:=../../utils/fileReader/build
SOURCE_FILE:=$(shell find -type f | \
	grep -E '*.c$$' | \
	sed -r 's/\./build/' | \
	sed -r 's/\.c/\.o/')

.DEFAULT_GOAL:=build/day06.out

build/:
	@mkdir build

build/%.o: %.c | build/
	@gcc -g -c -o $@ $<

clean:
	@rm -rf build/


build/day06.out: $(SOURCE_FILE) | build/
	@gcc -o $@ $(SOURCE_FILE) $(COMMON_LIB)/doubleBufferFileReader.o 

debugger: build/day06.out
	@gdb $< 

test: build/day06.out
	@./build/day06.out ../input/sample.txt

run: build/day06.out
	@./build/day06.out ../input/data.txt
