COMMON_LIB:=../../utils
FILE_LIB:=$(COMMON_LIB)/fileReader/build
BOOT_LIB:=$(COMMON_LIB)/bootCode/build
SOURCE_FILE:=$(shell find -type f | \
	grep -E '*.c$$' | \
	sed -r 's/\./build/' | \
	sed -r 's/\.c/\.o/')


#.DEFAULT_GOAL:=$(BIN)

build/:
	@mkdir build

build/%.o: %.c | build/
	@gcc -g -c -o $@ $<

clean:
	@rm -rf build/

build/day13.%.out: build/main.o build/%Schedule.o | build/
	@gcc -o $@ $^

dtest_%: build/day13.%.out
	@gdb --args $< 939 7,13,x,x,59,x,31,19

test_%: build/day13.%.out
	@$< 939 7,13,x,x,59,x,31,19

vtest_%: build/day13.%.out
	valgrind --leak-check=full --show-leak-kinds=all $< 939 7,13,x,x,59,x,31,19

drun_%: build/day13.%.out
	@gdb --args $< 1000391 19,x,x,x,x,x,x,x,x,x,x,x,x,37,x,x,x,x,x,383,x,x,x,x,x,x,x,23,x,x,x,x,13,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,29,x,457,x,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,17

run_%: build/day13.%.out
	@$< 1000391 19,x,x,x,x,x,x,x,x,x,x,x,x,37,x,x,x,x,x,383,x,x,x,x,x,x,x,23,x,x,x,x,13,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,29,x,457,x,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,17

vrun_%: build/day13.%.out
	valgrind --leak-check=yes $< 1000391 19,x,x,x,x,x,x,x,x,x,x,x,x,37,x,x,x,x,x,383,x,x,x,x,x,x,x,23,x,x,x,x,13,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x,29,x,457,x,x,x,x,x,x,x,x,x,41,x,x,x,x,x,x,17

check: build/day13.silver.out
	@$< 1000391 7,11,5

