#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <stdint.h>

int main(int argc, char* argv[])
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int a, b, x_c, x_asm, er = 0, over = 0;
    printf("Введіть значення з діапазону [-2147483648...2147483647]:\n");
    printf("a = "); scanf_s("%d", &a);
    printf("b = "); scanf_s("%d", &b);
    if (a > b)
    {
        if (a == 0)
        {
            printf("Помилка: ділення на 0!\n");
            return 1;
        }
        else
        {
            x_c = (52 * b) / a + b;
            if (x_c < INT32_MIN || x_c > INT32_MAX)
            {
                printf("Помилка: переповнення!\n");
                return 1;
            }
        }
    }
    else if (a < b)
    {
        if (b == 0)
        {
            printf("Помилка: ділення на 0!\n");
            return 1;
        }
        else if ((a - 5) < INT32_MIN || (a - 5) > INT32_MAX)
        {
            printf("Помилка: переповнення!\n");
            return 1;
        }
        else
        {
            x_c = (a - 5) / b;
        }
    }
    else
    {
        x_c = -125;
    }
    __asm
    {
        mov eax, a
        mov ebx, b
        cmp eax, ebx
        jg mark1
        je mark2
        jl mark3
        mark1 :
        cmp eax, 0
            je error1
            xchg eax, ebx
            mov ecx, 52
            imul ecx
            cmp ebx, eax
            jg overflow_error
            idiv ebx
            add eax, b
            jo overflow_error
            mov x_asm, eax
            jmp exit1
            mark2 :
        mov x_asm, -125
            jmp exit1
            mark3 :
        cmp ebx, 0
            je error3
            sub eax, 5
            jo overflow_error
            cdq
            idiv ebx
            mov x_asm, eax
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
        printf("Результат на мові С++ X = %d\n", x_c);
        printf("Результат на мові Assembler X = %d\n", x_asm);
    }
    system("Pause");
    return 0;
}