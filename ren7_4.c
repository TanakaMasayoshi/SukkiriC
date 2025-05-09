#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h> // toupper関数用

int main()
{
    int answer[3];
    int guess[3];
    int i, j, temp;
    int try_count = 0;
    char choice;

    srand((unsigned int)time(NULL)); // 乱数の初期化

    // 重複しない一桁のランダムな3つの数字を生成
    for (i = 0; i < 3;)
    {
        temp = rand() % 10;
        int duplicate = 0;

        for (j = 0; j < i; j++)
        {
            if (answer[j] == temp)
            {
                duplicate = 1;
                break;
            }
        }

        if (!duplicate)
        {
            answer[i] = temp;
            i++;
        }
    }

    printf("=== 数あてゲーム（0〜9の重複しない3桁）===\n");

    // ゲームループ
    while (1)
    {
        int hit = 0;
        int blow = 0;
        try_count++;

        printf("\n[%d回目] 数字を1つずつ入力してください:\n", try_count);

        for (i = 0; i < 3; i++)
        {
            while (1)
            {
                printf("%dつ目の数字: ", i + 1);
                scanf("%d", &guess[i]);

                if (guess[i] < 0 || guess[i] > 9)
                {
                    printf("⚠️ 0〜9の数字を入力してくださいまし！\n");
                    continue;
                }

                int duplicate = 0;
                for (j = 0; j < i; j++)
                {
                    if (guess[i] == guess[j])
                    {
                        printf("⚠️ 同じ数字は使えませんわ！\n");
                        duplicate = 1;
                        break;
                    }
                }

                if (!duplicate)
                    break;
            }
        }

        // ヒット・ブロー判定
        for (i = 0; i < 3; i++)
        {
            if (guess[i] == answer[i])
            {
                hit++;
            }
            else
            {
                for (j = 0; j < 3; j++)
                {
                    if (guess[i] == answer[j])
                    {
                        blow++;
                        break;
                    }
                }
            }
        }

        printf("結果 → %d ヒット, %d ブロー\n", hit, blow);

        if (hit == 3)
        {
            printf("🎉 お見事ですわ！%d回で正解なさいました！\n", try_count);
            break;
        }
        else
        {
            // 続けるか確認
            printf("まだ正解ではありませんわ。続けますか？（Y/N）: ");
            scanf(" %c", &choice);    // 前の改行をスキップするために空白を入れる
            choice = toupper(choice); // 小文字も大文字に変換

            if (choice != 'Y')
            {
                printf("💤 ゲームを終了しますわ。正解は %d %d %d でした。\n", answer[0], answer[1], answer[2]);
                break;
            }
        }
    }

    return 0;
}
