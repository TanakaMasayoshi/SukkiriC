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
    printf("a 足す b は %d\n", a + b);
    printf("a 引く b は %d\n", a - b);
    printf("a かける b は %d\n", a * b);
    printf("a 割る b の商は %d\n", a / b);
    printf("a 割る b の余り(剰余)は %d\n", a % b);
    return 0;
}