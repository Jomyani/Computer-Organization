// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>

int main()
{
	//encode
	__asm {
		ror al, 1			//rotate 1 bit to the right

		ror al, 4			//rotate 4 bits to the right, swapping nibbles 

		xor ebx, ebx		//reverse bit order
		xor ecx, ecx
		mov ecx, 8			//set ecx to 8 to run through 8 bits
	REVERSE:
		rol al, 1			//sets cf to 1 if left-most bit is 1, otherwise 0
		jb ONE				//jump if cf=1
		ror bl, 1			//rotate bl, keeps bit at 0
		dec ecx			
		cmp ecx, 0			//check if end of loop
		jne REVERSE			
		je END				
	ONE:
		ror bl, 1			//rotates bit
		inc bl				//set next bit to 1
		dec ecx
		cmp ecx, 0			//check if end of loop
		jne REVERSE
	END:
		ror bl				//final rotate 
		mov al, bl			//put the reversed value into al

		xor ebx, ebx		//swap half nibbles
		mov bl, al			
		and bl, 0x0F		//zero out first half of bl
		and al, 0xF0		//zero out second half of al
		xor edx, edx
		ror bl, 2			//rotate bl to have first 2 bits in first half of bl and second 2 in second half
		mov dl, bl			
		and dl, 0xF0		//put bl into dl and zero out second half of dl
		ror dl, 4			//rotate to align the 2 bits into the end of second half 
		and bl, 0x0F		//zero out first half of bl 
		or dl, bl			//or dl with bl to get reversed half nibbles in second half
		xor edx, edx
		ror al, 2			//rotate al to have first 2 bits in second half of al and second 2 in first half
		mov dl, al			
		and dl, 0x0F		//put al into dl and zero out first half of dl
		ror dl, 4			//rotate to align the 2 bits into the beginning of first half
		and al, 0xF0		//zero out second half of al
		or al, dl			//or dl with al to get reversed half nibbles in first half
		or al, bl			//or bl and al to combine the nibbles

		rol al, 1			//rotate 1 bit to left
	}

	//decode
	__asm {
		ror al, 1			//rotate 1 bit to the right

		xor ebx, ebx		//swap half nibbles
		mov bl, al
		and bl, 0x0F		//zero out first half of bl
		and al, 0xF0		//zero out second half of al
		xor edx, edx
		ror bl, 2			//rotate bl to have first 2 bits in first half of bl and second 2 in second half
		mov dl, bl
		and dl, 0xF0		//put bl into dl and zero out second half of dl
		ror dl, 4			//rotate to align the 2 bits into the end of second half 
		and bl, 0x0F		//zero out first half of bl 
		or dl, bl			//or dl with bl to get reversed half nibbles in second half
		xor edx, edx
		ror al, 2			//rotate al to have first 2 bits in second half of al and second 2 in first half
		mov dl, al
		and dl, 0x0F		//put al into dl and zero out first half of dl
		ror dl, 4			//rotate to align the 2 bits into the beginning of first half
		and al, 0xF0		//zero out second half of al
		or al, dl			//or dl with al to get reversed half nibbles in first half
		or al, bl			//or bl and al to combine the nibbles

		xor ebx, ebx		//reverse bit order
		xor ecx, ecx
		mov ecx, 8			//set ecx to 8 to run through 8 bits
	REVERSE:
		rol al, 1			//sets cf to 1 if left-most bit is 1, otherwise 0
		jb ONE				//jump if cf=1
		ror bl, 1			//rotate bl, keeps bit at 0
		dec ecx
		cmp ecx, 0			//check if end of loop
		jne REVERSE
		je END
	ONE:
		ror bl, 1			//rotates bit
		inc bl				//set next bit to 1
		dec ecx
		cmp ecx, 0			//check if end of loop
		jne REVERSE
	END:
		ror bl				//final rotate 
		mov al, bl			//put the reversed value into al

		ror al, 4			//rotate 4 bits to the right, swapping nibbles 

		rol al, 1			//rotate 1 bit to left
	}

}

