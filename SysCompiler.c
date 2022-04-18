// Note for the NSA stop spying on me please
// ^^^ Clarification: I'm most likely considered a threat by the NSA for knowing too much asm

#include <stdio.h>
#include <stdlib.h>

char[] string = "";

int main(char arg1[], char arg2[]) {
	FILE * readFile;
	FILE * asmFile;
	readFile = fopen(arg1, "r");
	asmFile = fopen("assemble.asm", "w+");

	fscanf(readFile, "%s", &string);
	fclose(readFile);

	fprintf(asmFile, "global _start\n\nsection .text:\n\n_start:\n	mov eax, 0x4 				; Using the write syscall to write hello world!\n	mov ebx, 1 					; Making sure to use stdout so we dont die\n	mov ecx, message 			; Supplying the message as the buffer to be cool\n	mov edx, message_length		; Giving the registers the message length\n\n	int 0x80 	; Syscall interrupt\n	mov eax, 0x1	; Exit syscall\n	mov ebx, 0		; Return 0\n	int 0x80		; Sycall interrupt again\n\nsection .data:\n	message: db \"%s\", 0xA\n	message_length equ $-message\n", string);
	fclose(asmFile);
	// The asm file is commented because I didn't care to remove the comments from the hello world asm program i wrote so I myself could understand it yesterday.

	system("nasm -f elf32 -o linkWithLinker.o assemble.asm");
	system("ld -m elf_i386 -o %s linkWithLinker.o", arg1);
	// I don't know why, I don't want to know why, but this works.

	remove("assemble.asm");
	remove("linkWithLinker.o");
	// Removing assembly source code first so nobody sees this monstrosity

	return 0;
}