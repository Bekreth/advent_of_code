SOURCE_FILE:=$(shell find -type f | \
	grep -E '*.c$$' | \
	sed -r 's/\./build/' | \
	sed -r 's/\.c/\.o/')

.DEFAULT_GOAL:=build/day03.out

build/:
	@mkdir build

build/%.o: %.c | build/
	@gcc -g -c -o $@ $<

clean:
	@rm -rf build/


build/day03.out: $(SOURCE_FILE) | build/
	@gcc -o $@ $(SOURCE_FILE)

debugger: build/day03.out
	@gdb $<

test: build/day03.out
	@./build/day03.out ../input/sample.txt

run: build/day03.out
	@./build/day03.out ../input/data.txt
