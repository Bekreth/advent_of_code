SOURCE_FILE:=$(shell find -type f | \
	grep -E '*.c$$' | \
	sed -r 's/\./build/' | \
	sed -r 's/\.c/\.o/')

.DEFAULT_GOAL:=build/day04.out

build/:
	@mkdir build

build/%.o: %.c | build/
	@gcc -g -c -o $@ $<

clean:
	@rm -rf build/


build/day04.out: $(SOURCE_FILE) | build/
	@gcc -o $@ $(SOURCE_FILE)

debugger: build/day04.out
	@gdb $< 

test: build/day04.out
	@./build/day04.out ../input/micro.txt

run: build/day04.out
	@./build/day04.out ../input/data.txt
