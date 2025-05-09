#include <stdio.h>
#include <stdlib.h>

typedef char String[1024];

int main(void)
{
    String num1;
    printf("正の整数を入力してください。\n");
    printf("整数a:");
    scanf("%s", num1);
    int a = atoi(num1);
    int b = 0;
    while (a > b)
    {
        b = b + 1;
        if (a == b)
            printf("%d", b);
        else if (b % 10 == 0)
            printf("%d\n", b);
        else
            printf("%d,", b);
    };
    return 0;
}