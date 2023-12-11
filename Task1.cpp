#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char a, b, x_c, x_asm;
    printf("Введіть значення з діапазону [-128...127]:\n");
    printf("a = "); scanf_s("%hhd", &a);
    printf("b = "); scanf_s("%hhd", &b);
    if (a > b)
    {
        x_c = b / a + 1;
    }
    else if (a == b)
    {
        x_c = -20;
    }
    else
    {
        x_c = (a - 45) * b;
    }
    printf("Результат на мові С++ X = %hhd\n", x_c);
    __asm
    {
        mov al, a
        mov bl, b
        cmp al, bl
        jg mark1
        je mark2
        jl mark3
        mark1 :
        xchg al, bl
            cbw
            idiv bl
            add al, 1
            mov x_asm, al
            jmp exit1
            mark2 :
        mov x_asm, -20
            jmp exit1
            mark3 :
        sub al, 45
            imul bl
            mov x_asm, al
            jmp exit1
            exit1 :
    }
    printf("Результат на мові Assembler X = %hhd\n", x_asm);
    system("Pause");
    return 0;
}