#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[1024];
} Monster;

void doBattle(const char *playerName, int battleNumber, Monster monster, int *victoryCount)
{
    printf("%sが現れた！\n", monster.name);
    printf("%sを倒した！\n", monster.name);
    (*victoryCount)++;
}

void doDungeon(const char *playerName)
{
    Monster monsters[5] = {
        {"スライム"},
        {"ゴブリン"},
        {"オオコウモリ"},
        {"ウェアウルフ"},
        {"ドラゴン"}};

    int victoryCount = 0;

    printf("%sはダンジョンに到着した\n", playerName);

    for (int i = 0; i < 5; i++)
    {
        doBattle(playerName, i + 1, monsters[i], &victoryCount);
    }

    printf("%sはダンジョンを制覇した！\n", playerName);
    printf("***GAME CLEARED!***\n");
    printf("倒したモンスターの数=%d\n", victoryCount);
}

int main(int argc, char **argv)
{
    char playerName[1024];
    if (argc != 2)
    {
        printf("エラー：プレイヤー名を入力してください: ");
        scanf("%1023s", playerName);
    }
    else
    {
        snprintf(playerName, sizeof(playerName), "%s", argv[1]);
    }
    printf("***Puzzle & Monsters ***\n");
    doDungeon(playerName);

    return 0;
}
