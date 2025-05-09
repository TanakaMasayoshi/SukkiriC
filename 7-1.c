#include <stdio.h>

int main(void)
{
    int a[4][5] = {
        {123, 456, 789, 101, 121},
        {314, 151, 617, 181, 920},
        {212, 223, 242, 526, 272},
        {829, 303, 132, 333, 435}};

    printf("2次配列aの値を表示\n");
    for (int i = 0; i < 4; i++)
    {
        printf("a[%d][0-4]: ", i);
        for (int j = 0; j < 5; j++)
        {
            printf("%d", a[i][j]);
            if (j < 4)
            {
                printf(", ");
            }
        }
        printf("\n");
    }

    return 0;
}
