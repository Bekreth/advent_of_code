COMMON_LIB:=../../utils
HASH_TABLE_LIB:=$(COMMON_LIB)/hashTable/build
SOURCE_FILE:=$(shell find -type f | \
	grep -E '*.c$$' | \
	sed -r 's/\./build/' | \
	sed -r 's/\.c/\.o/')
BIN:=build/day15.out

INPUT_0=0,3,6
INPUT_1=1,3,2
INPUT_2=1,2,3
INPUT_3=2,3,1
INPUT_4=3,2,1
INPUT_5=3,1,2
INPUT_6=8,13,1,0,18,9

.DEFAULT_GOAL:=$(BIN)

build/:
	@mkdir build

build/%.o: %.c | build/
	@gcc -g -c -o $@ $<

clean:
	@rm -rf build/


$(BIN): $(SOURCE_FILE) | build/
	@gcc -o $@ $(SOURCE_FILE) \
	$(HASH_TABLE_LIB)/hashTable.o

debugger: $(BIN) 
	@gdb $< 

run_%: $(BIN)
	@$< $(INPUT_$*)

vrun_%: $(BIN)
	valgrind --leak-check=yes $(BIN) $%

