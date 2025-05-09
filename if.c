#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef char String[1024];

int main(void)
{
    String num1 = "a";
    String num2 = "b";
    printf("2つの整数を入力してください。\n");
    printf("整数a:");
    scanf("%s",num1);
    printf("整数b:");
    scanf("%s",num2);
    int a = atoi(num1);
    int b = atoi(num2);

    if(a % b == 0)
    printf("a は b の倍数です。");
    else
    printf("a は b の倍数ではありません。");
    return 0;
}