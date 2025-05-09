#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef char String[1024];

int main(void)
{
    typedef struct
    {
        String name;
        int hp;
        int satiety;
    } Player;
    Player p = {"", 0, 0};
    String strSatiety;
    printf("Playerのパラメータを設定してください\n");
    printf("名前：");
    scanf("%s", p.name);
    printf("満腹度(Max100):");
    scanf("%s", strSatiety);
    p.satiety = atoi(strSatiety);
    srand((unsigned)time(NULL));
    p.hp = rand() % 1000;
    while (p.satiety > 100 || p.satiety < 0)
    {
        printf("範囲外です、設定し直してください\n");
        printf("満腹度(Max100):");
        scanf("%s", strSatiety);
        p.satiety = atoi(strSatiety);
    }
    printf("あなたの名前は%sです\n", p.name);
    printf("HPは%dです\n", p.hp);
    if (p.satiety >= 60)
    {
        printf("満腹度は%d、満腹ですね\n", p.satiety);
    }
    else
    {
        printf("満腹度は%d、お腹減ってますね\n", p.satiety);
    }

    return 0;
}