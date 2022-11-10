SOURCE_FILE:=$(shell find -type f | \
	grep -E '*.c$$' | \
	sed -r 's/\./build/' | \
	sed -r 's/\.c/\.o/')

.DEFAULT_GOAL:=build/day05.out

build/:
	@mkdir build

build/%.o: %.c | build/
	@gcc -g -c -o $@ $<

clean:
	@rm -rf build/


build/day05.out: $(SOURCE_FILE) | build/
	@gcc -o $@ $(SOURCE_FILE)

debugger: build/day05.out
	@gdb $< 

test: build/day05.out
	@./build/day05.out ../input/sample.txt

run: build/day05.out
	@./build/day05.out ../input/data.txt
