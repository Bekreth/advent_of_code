section .data
	;INPUT db "./input.txt", 0
	INPUT db "./sample.txt", 0

section .text
	global _start

_start:
	;; Get the heap start
	mov rax, 12
	mov rdi, 0
	syscall
	mov r15, rax

	jmp .open_file
	jmp .read_input
	jmp .close_file
	jmp .exit

.open_file:
	mov rax, 2
	lea rdi, [INPUT]
	mov rsi, 0
	mov rdx, 0
	push rdx
	syscall

.read_input:
	;; Read From File
	mov rdi, rax	; from STDIN
	mov rax, r10	; READ
	mov rsi, rsp	; into RSP
	mov rdx, 0xFF	; 256 bytes
	syscall
	mov r14, rax		; move byte read count into r14

	;; Push to Heap
	mov rax, 12
	mov rdi, r14
	syscall
	mov r15, rsp

	;; Read data from heap
	mov rax, 1		; WRITE
	mov rdi, 1		; into STDOUT
	mov rsi, r15	; from rsp
	mov rdx, r14		; 2 bytes
	syscall


.close_file:
	mov rax, 3
	pop rdi
	syscall

.exit:
	mov rax, 60		; exit (
	mov rdi, 0		; EXIT_SUCCESS
	syscall

