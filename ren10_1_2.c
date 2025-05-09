#include <stdio.h>
#include <string.h>

void sub(char ages[3])
{
    for (int i = 0; i < 3; i++)
    {
        printf("%d番目：%d\n", i + 1, ages[i]);
    }
}

int main(void)
{
    char a[] = {1, 2, 3};
    sub(a);
    printf("正常にコピーされました\n");
    return 0;
}