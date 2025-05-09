#include <stdio.h>

int main(void)
{
    int a[6][6] = {
        {1, 1, 1, 1, 1, 1},
        {1, 0, 1, 2, 0, 1},
        {1, 0, 1, 1, 0, 1},
        {1, 0, 0, 1, 0, 1},
        {1, 1, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1},

    };

    for (int i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            if (a[i][j] == 1)
                printf("口");
            else if (a[i][j] == 0)
                printf("・");
            else
                printf("下");
        }
        printf("\n");
    }

    return 0;
}
