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
        int atk;
    } Player;
    Player p = {"", 0, 0, 0};
    typedef struct
    {
        String name;
        int hp;
        int atk;
    } Enemy;
    Enemy e = {"", 0, 0};
    String strSatiety;
    printf("Playerのパラメータを設定してください\n");
    printf("名前：");
    scanf("%s", p.name);
    printf("満腹度(Max100):");
    scanf("%s", strSatiety);
    p.satiety = atoi(strSatiety);
    srand((unsigned)time(NULL));
    p.hp = rand() % 1000;
    p.atk = rand() % 101;
    e.hp = rand() % 1000;
    e.atk = rand() % 101;

    while (p.satiety > 100 || p.satiety < 0)
    {
        printf("範囲外です、設定し直してください\n");
        printf("満腹度(Max100):");
        scanf("%s", strSatiety);
        p.satiety = atoi(strSatiety);
    }
    printf("\n");
    printf("Enemyのパラメータを設定してください\n");
    printf("名前：");
    scanf("%s", e.name);
    printf("あなたの名前は%sです\n", p.name);
    printf("HPは%d、攻撃力は%dです\n", p.hp, p.atk);
    if (p.satiety >= 60)
        printf("満腹度は%d、満腹ですね\n\n", p.satiety);
    else
        printf("満腹度は%d、お腹減ってますね\n\n", p.satiety);
    printf("敵の名前は%sです\n", e.name);
    printf("HPは%d、攻撃力は%dです\n\n", e.hp, e.atk);
    if (p.atk >= e.atk)
        printf("攻めよう\n");
    else
        printf("逃げよう\n");
    return 0;
}