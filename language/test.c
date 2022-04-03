
#include <stdio.h>
#include <setjmp.h>

jmp_buf buf;

int lol = 0;

void f()
{
    printf("%d\n", lol);
}

int main()
{
    if (1)
    {
        int lol = 1;
        {
            printf("%d\n", lol);
            f();
        }
        if (lol) { {} int qwe = 123; }
    }
}
