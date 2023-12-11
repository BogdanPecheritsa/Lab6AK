#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    short a, b, x_c, x_asm, er = 0, over = 0;
    printf("Введіть значення з діапазону [-32768...32767]:\n");
    printf("a = "); scanf_s("%hd", &a);
    printf("b = "); scanf_s("%hd", &b);
    if (a > b)
    {
        if (a == 0)
        {
            printf("Помилка: ділення на 0!\n");
            return 1;
        }
        else
        {
            if (b > INT16_MAX / a) {
                printf("Помилка: переповнення!\n");
                return 1;
            }
            x_c = (b / a) + 1;
        }
    }
    else if (a < b)
    {
        if (b == 0)
        {
            printf("Помилка: ділення на 0!\n");
            return 1;
        }
        else if ((a - 45) < -32768 || (a - 45) > 32767)
        {
            printf("Помилка: переповнення!\n");
            return 1;
        }
        else
        {
            x_c = (a - 45) / b;
        }
    }
    else
    {
        x_c = -20;
    }
    printf("Результат на мові С++ X = %hd\n", x_c);
    __asm
    {
        mov ax, a
        mov bx, b
        cmp ax, bx
        jg mark1
        je mark2
        jl mark3
        mark1 :
        cmp ax, 0
            je error1
            xchg ax, bx
            idiv bx
            add ax, 1
            jo overflow_error
            mov x_asm, ax
            jmp exit1
            mark2 :
        mov x_asm, -20
            jmp exit1
            mark3 :
        cmp bx, 0
            je error3
            sub ax, 45
            jo overflow_error
            cwd
            idiv bx
            mov x_asm, ax
            jmp exit1
            error1 :
        mov er, 1
            jmp exit1
            overflow_error :
        mov over, 1
            jmp exit1
            error3 :
        mov er, 1
            jmp exit1
            exit1 :
    }
    if (er == 1)
    {
        printf("Помилка: ділення на 0!\n");
    }
    else if (over == 1)
    {
        printf("Помилка: переповнення!\n");
    }
    else
    {
        printf("Результат на мові Assembler X = %hd\n", x_asm);
    }
    system("Pause");
    return 0;
}