// These are simplified Roman numerals. Instead of IV for 4, we just use IIII. It is a little easier.
// No "subtractive notation", only "additive notation" in en.wikipedia.org/wiki/Roman_numerals
// All letters must be in order M-D-C-L-X-V-I. Up to four each M-C-X-I and up to one D-L-V.
// 2,618 would be MMDCXVIII (2000 + 500 + 100 + 10 + 5 + 3)
// 24 is XXIIII, 50 is just L, 1001 is MI, and so on. All numbers are positive.
// 4,999 is the largest and longest, MMMMDCCCCLXXXXVIIII. Whew.

// All input is on the command line. Do not prompt for values.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n;
char result[100];

int main(int argc, char* argv[]) {
    int i;
    for (i = 1; i < argc; i++) {
        n = atoi(argv[i]);
        if (n > 0 && n < 5000) {
            __asm {
                // TBD -- Convert 'n' to a string in 'result'
                // Hints:
                // 1. Use 4 registers as follows:
                //    EAX = remaining number (14, e.g.), starts with n
                xor eax, eax
                mov eax, n

                //    EDI = Next available location in result
                mov edi, dword ptr [result]
                lea edi, result
                //    EBX = The letter to consider showing ('X', e.g.)
                //    ECX = The value of the letter (10, e.g.)
                // 2. Call an assembly function for each letter in this order
                //    1000 (M) call this 4 times
                mov ecx, 1000
                mov bl, 'M'
                call check
                mov ecx, 1000
                mov bl, 'M'
                call check
                mov ecx, 1000
                mov bl, 'M'
                call check
                mov ecx, 1000
                mov bl, 'M'
                call check

                //    500 (D) call this once
                mov ecx, 500
                mov bl, 'D'
                call check

                //    100 (C) call this 4 times
                mov ecx, 100
                mov bl, 'C'
                call check
                mov ecx, 100
                mov bl, 'C'
                call check
                mov ecx, 100
                mov bl, 'C'
                call check
                mov ecx, 100
                mov bl, 'C'
                call check

                //    50 (L) call this once
                mov ecx, 50
                mov bl, 'L'
                call check

                //    10 (X) call this 4 times
                mov ecx, 10
                mov bl, 'X'
                call check
                mov ecx, 10
                mov bl, 'X'
                call check
                mov ecx, 10
                mov bl, 'X'
                call check
                mov ecx, 10
                mov bl, 'X'
                call check

                //    5 (V) call this once
                mov ecx, 5
                mov bl, 'V'
                call check

                //    1 (I) call this 4 times
                mov ecx, 1
                mov bl, 'I'
                call check
                mov ecx, 1
                mov bl, 'I'
                call check
                mov ecx, 1
                mov bl, 'I'
                call check
                mov ecx, 1
                mov bl, 'I'
                call check

                jmp ender

                check:
                    push ecx
                    push ebx
                    push edi
                    push eax

                    xor edx, edx
                    div ecx

                    pop eax
                    push eax
                    cmp eax, edx
                    jz notContained

                    pop eax
                    pop edi
                    pop ebx
                    push eax
                    mov byte ptr [edi], bl
                    inc edi

                    pop eax
                    pop ecx
                    sub eax, ecx
                    ret

                    notContained:
                        pop eax
                        pop edi
                        pop ebx
                        pop ecx
                        ret

                ender:
                    nop
            }
            printf("Roman(%d) = %s\n", n, result);
        }
    }
    system("pause");
}