#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void fillRandNums(int *arry, int length, int min, int max)
{
    int range = max - min + 1;

    if (range < length)
    {
        printf("エラー: 範囲内に重複なしで入る数が足りません。\n");
        return;
    }

    int *used = (int *)calloc(range, sizeof(int)); // 使用済みチェック配列

    srand((unsigned int)time(NULL)); // UNIX時間で乱数の種を初期化

    int count = 0;
    while (count < length)
    {
        int num = rand() % range + min;
        if (!used[num - min])
        { // まだ使っていない数なら
            arry[count++] = num;
            used[num - min] = 1;
        }
    }

    free(used);
}

int main(void)
{
    int arry[11];
    int length = 11;
    int min = -5, max = 5;

    fillRandNums(arry, length, min, max);

    printf("生成された乱数配列（重複なし・負数対応）:\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d ", arry[i]);
    }
    printf("\n");

    return 0;
}
