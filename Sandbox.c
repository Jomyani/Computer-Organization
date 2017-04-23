#include <stdio.h>
#include <windows.h>

void main() {
	int test1 = 0xA5;
	int test2, test3, test4, test5, test6;

		__asm {
			mov eax, test1
			ror al, 1
			mov test2, eax
			ror al, 4
			mov test3, eax
			ror al, 6
			mov test4, eax
			xor ebx, ebx
			mov bl, al
			and bl, 0x0F
			and al, 0xF0
			xor edx, edx
			ror bl, 2
			mov dl, bl
			and dl, 0xF0
			ror dl, 4
			and bl, 0x0F
			or dl, bl
			xor edx, edx
			ror al, 2
			mov dl, al
			and dl, 0x0F
			ror dl, 4
			and al, 0xF0
			or al, dl
			or al, bl
			mov test5, eax
			rol al, 1
			mov test6, eax
	}
		printf("\n Test1 = %x\n, Test2 = %x\n, Test3 = %x\n, Test4 = %x\n, Test5 = %x\n, Test6 = %x\n", test1, test2, test3, test4, test5, test6);
}