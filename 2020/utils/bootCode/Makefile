SOURCE_FILE:=$(shell find -type f | \
	grep -E '*.c$$' | \
	sed -r 's/\./build/' | \
	sed -r 's/\.c/\.o/')

.DEFAULT_GOAL:=compile

build/:
	@mkdir build

build/%.o: %.c | build/
	@gcc  -c -o $@ $<

clean:
	@rm -rf build/

compile: $(SOURCE_FILE) | build/
