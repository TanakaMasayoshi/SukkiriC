#include <stdio.h>
#include <stdlib.h>

typedef char String[1024];

int main(void)
{
    String num1 = "a";
    String num2 = "b";
    printf("2つの整数を入力してください。\n");
    printf("整数a:");
    scanf("%s", num1);
    int a = atoi(num1);
    printf("整数b:");
    scanf("%s", num2);
    int b = atoi(num2);
    if (a == b)
        printf("２つの値は等しい");
    else if (a > b)
        printf("大きい方は %d、小さい方は %dです。", a, b);
    else
        printf("大きい方は %d、小さい方は %dです。", b, a);
    return 0;
}