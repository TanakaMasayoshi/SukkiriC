#include <stdio.h>

typedef char String[1024];

int main(void)
{
    String color = "オルガ";
    String name = "五日";
    printf("%s", color + name); // オルガ五日にしたくて…
    return 0;
}