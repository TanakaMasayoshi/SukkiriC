#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef enum Element
{
    FIRE,
    WATER,
    WIND,
    EARTH,
    LIFE,
    EMPTY
} Element;

const char ELEMENT_SYMBOLS[EMPTY + 1] = {'$', '~', '@', '#', '&', ' '};

const int ELEMENT_COLORS[EMPTY + 1] = {1, 6, 2, 3, 5, 0};

enum
{
    MAX_GEMS = 14
};

typedef struct MONSTER
{
    char *name;
    Element element;
    int maxhp;
    int hp;
    int attack;
    int defense;
} Monster;

typedef struct DUNGEON
{
    Monster *monsters;
    int numMonsters;
} Dungeon;

typedef struct PARTY
{
    char *playerName;
    Monster *monsters;
    int numMonsters;
    int maxhp;
    int hp;
    int defense;
} Party;

typedef struct BATTLE_FIELD
{
    Party *pParty;
    Monster *pEnemy;
    Element gems[MAX_GEMS];
} BattleField;

int goDungeon(Party *pParty, Dungeon *pDungeon);
int doBattle(Party *pParty, Monster *pEnemy);
Party organizeParty(char *playerName, Monster *monsters, int numMonsters);
void showParty(Party *pParty);
void onPlayerTurn(BattleField *pField);
void doAttack(BattleField *pField);
void onEnemyTurn(BattleField *pField);
void doEnemyAttack(BattleField *pField);
void showBattleField(BattleField *pField);

void fillGems(BattleField *pField);
void printGems(BattleField *pField);
void printGem(Element element);
void printMonsterName(Monster *monster);

int main(int argc, char **argv)
{
    srand((unsigned)time(NULL));
    if (argc != 2)
    {
        printf("エラー：プレイヤー名を入力してください\n");
        return 1;
    }

    printf("*** Puzzle & Monsters ***\n");

    Monster partyMonsters[] = {
        {"朱雀", FIRE, 150, 150, 25, 10},
        {"青龍", WATER, 130, 130, 20, 15},
        {"白虎", WIND, 140, 140, 22, 12},
        {"玄武", EARTH, 160, 160, 18, 20}};

    Party party = organizeParty(argv[1], partyMonsters, 4);

    Monster dungeonMonster[] = {
        {"スライム", WATER, 100, 100, 10, 5},
        {"ゴブリン", EARTH, 200, 200, 20, 15},
        {"オオコウモリ", WIND, 300, 300, 30, 25},
        {"ウェアウルフ", WIND, 400, 400, 40, 30},
        {"ドラゴン", FIRE, 800, 800, 50, 40}};

    Dungeon dungeon = {dungeonMonster, 5};
    int victoryCount = goDungeon(&party, &dungeon);

    if (victoryCount == dungeon.numMonsters)
    {
        printf("ゲームクリア！\n");
    }
    else
    {
        printf("ゲームオーバー\n");
    }

    printf("倒したモンスターの数=%d\n", victoryCount);
    return 0;
}

int goDungeon(Party *pParty, Dungeon *pDungeon)
{
    printf("%sのパーティ(HP=%d)はダンジョンに到着した\n", pParty->playerName, pParty->hp);
    showParty(pParty);
    int victoryCount = 0;
    for (int i = 0; i < pDungeon->numMonsters; i++)
    {
        victoryCount += doBattle(pParty, &(pDungeon->monsters[i]));
        if (pParty->hp <= 0)
        {
            printf("%sはダンジョンから逃げ出した...\n", pParty->playerName);
            break;
        }
        else
        {
            printf("%sはさらに奥へと進んだ\n\n", pParty->playerName);
            printf("================\n\n");
        }
    }
    return victoryCount;
}

int doBattle(Party *pParty, Monster *pEnemy)
{
    BattleField field = {pParty, pEnemy};
    printMonsterName(pEnemy);
    printf("が現れた！\n");
    fillGems(&field);
    while (pParty->hp > 0 && pEnemy->hp > 0)
    {
        onPlayerTurn(&field);
        if (pEnemy->hp <= 0)
            break;
        onEnemyTurn(&field);
        if (pParty->hp <= 0)
            break;
    }
    if (pEnemy->hp <= 0)
        printMonsterName(pEnemy);
    printf("を倒した！\n");
    return 1;
}

Party organizeParty(char *playerName, Monster *monsters, int numMonsters)
{
    int sumHp = 0;
    int sumDefense = 0;
    for (int i = 0; i < numMonsters; i++)
    {
        sumHp += monsters[i].hp;
        sumDefense += monsters[i].defense;
    }
    int avgDefense = sumDefense / numMonsters;

    Party p = {playerName, monsters, numMonsters, sumHp, sumHp, avgDefense};
    return p;
}

void showParty(Party *pParty)
{
    printf("＜パーティ編成＞----------\n");
    for (int i = 0; i < pParty->numMonsters; i++)
    {
        printMonsterName(&(pParty->monsters[i]));
        printf("  HP=%4d 攻撃=%3d 防御=%3d\n",
               pParty->monsters[i].hp,
               pParty->monsters[i].attack,
               pParty->monsters[i].defense);
    }
    printf("------------------------\n\n");
}

void onPlayerTurn(BattleField *pField)
{
    printf("\n【%sのターン】\n", pField->pParty->playerName);
    showBattleField(pField);
    doAttack(pField);
}

void doAttack(BattleField *pField)
{
    pField->pEnemy->hp -= 80; // 修正：pField->pEnemy にアクセス
    printf("ダミー攻撃で80のダメージを与えた\n");
}

void onEnemyTurn(BattleField *pField)
{
    printf("\n【%sのターン】\n", pField->pEnemy->name); // 修正：pField->pEnemy にアクセス
    doEnemyAttack(pField);
}

void doEnemyAttack(BattleField *pField)
{
    pField->pParty->hp -= 20; // 修正：pField->pParty にアクセス
    printf("20のダメージを受けた\n");
}

void showBattleField(BattleField *pField)
{
    printf("--------------------\n\n");
    printMonsterName(pField->pEnemy);
    printf("\n HP= %d/%d\n", pField->pEnemy->hp, pField->pEnemy->maxhp); // 修正：maxhp を使う
    for (int i = 0; i < pField->pParty->numMonsters; i++)
    {
        printMonsterName(&(pField->pParty->monsters[i]));
        printf("  ");
    }
    printf("\nHP= %d/%d\n", pField->pParty->hp, pField->pParty->maxhp);
    printf("------------------------------\n");
    printf(" ");
    for (int i = 0; i < MAX_GEMS; i++)
    {
        printf("%c ", 'A' + i);
    }
    printf("\n");
    printGems(pField);
    printf("------------------------------\n");
}

void fillGems(BattleField *pField)
{
    for (int i = 0; i < MAX_GEMS; i++)
    {
        pField->gems[i] = rand() % EMPTY;
    }
}

void printGems(BattleField *pField)
{
    for (int i = 0; i < MAX_GEMS; i++)
    {
        printf(" ");
        printGem(pField->gems[i]);
    }
    printf("\n");
}

void printGem(Element element)
{
    int colgem = ELEMENT_COLORS[element];
    char symgem = ELEMENT_SYMBOLS[element];
    printf("\x1b[30m");
    printf("\x1b[4%dm", colgem);
    printf("%c", symgem);
    printf("\x1b[0m");
}

void printMonsterName(Monster *monster)
{
    char symbol = ELEMENT_SYMBOLS[monster->element];

    printf("\x1b[3%dm", ELEMENT_COLORS[monster->element]);
    printf("%c%s%c", symbol, monster->name, symbol);
    printf("\x1b[0m");
}
