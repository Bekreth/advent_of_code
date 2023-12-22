
solution.o: solution.asm
	nasm -f elf64 -o $@ $<

solution: solution.o
	ld -o $@ $<

run: solution
	./solution
