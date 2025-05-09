#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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
const char ELEMENT_COLORS[EMPTY + 1] = {1, 6, 2, 3, 5, 0};

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
    const int numMonsters;
} Dungeon;

typedef struct PARTY
{
    char *playerName;
    Monster *monsters;
    const int numMonsters;
    const int maxHp;
    int hp;
    const int defense;
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

void printMonsterName(Monster *monster);
void fillGems(Element *gems);
void printGems(Element *gems);
void printGem(Element element);

int main(int argc, char **argv)
{
    srand((unsigned)time(NULL));

    if (argc != 2)
    {
        printf("エラー: プレイヤー名を指定して起動してください\n");
        return 1;
    }

    printf("*** Puzzle & Monsters ***\n");

    Monster partyMonsters[] = {
        {"朱雀", FIRE, 150, 150, 25, 10},
        {"青龍", WIND, 150, 150, 15, 10},
        {"白虎", EARTH, 150, 150, 20, 5},
        {"玄武", WATER, 150, 150, 20, 15}};
    Party party = organizeParty(argv[1], partyMonsters, 4);

    Monster dungeonMonsters[] = {
        {"スライム", WATER, 100, 100, 10, 5},
        {"ゴブリン", EARTH, 200, 200, 20, 15},
        {"オオコウモリ", WIND, 300, 300, 30, 25},
        {"ウェアウルフ", WIND, 400, 400, 40, 30},
        {"ドラゴン", FIRE, 800, 800, 50, 40}};
    Dungeon dungeon = {dungeonMonsters, 5};

    int winCount = goDungeon(&party, &dungeon);

    if (winCount == dungeon.numMonsters)
    {
        printf("***GAME CLEAR!***\n");
    }
    else
    {
        printf("***GAME OVER***\n");
    }
    printf("倒したモンスター数＝%d\n", winCount);
    return 0;
}

int goDungeon(Party *pParty, Dungeon *pDungeon)
{
    printf("%sのパーティ(HP=%d)はダンジョンに到着した\n", pParty->playerName, pParty->hp);
    showParty(pParty);

    int winCount = 0;
    for (int i = 0; i < pDungeon->numMonsters; i++)
    {
        winCount += doBattle(pParty, &(pDungeon->monsters[i]));
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

    printf("%sはダンジョンを制覇した！\n", pParty->playerName);
    return winCount;
}

int doBattle(Party *pParty, Monster *pEnemy)
{
    printMonsterName(pEnemy);
    printf("が現れた！\n");

    BattleField field = {pParty, pEnemy};
    fillGems(field.gems);

    while (true)
    {
        onPlayerTurn(&field);
        if (pEnemy->hp <= 0)
        {
            printMonsterName(pEnemy);
            printf("を倒した！\n");
            return 1;
        }
        onEnemyTurn(&field);
        if (pParty->hp <= 0)
        {
            printf("%sは倒れた...\n", pParty->playerName);
            return 0;
        }
    }
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
    pField->pEnemy->hp -= 80;
    printf("ダミー攻撃で80のダメージを与えた\n");
}

void onEnemyTurn(BattleField *pField)
{
    printf("\n【%sのターン】\n", pField->pEnemy->name);
    doEnemyAttack(pField);
}

void doEnemyAttack(BattleField *pField)
{
    pField->pParty->hp -= 20;
    printf("20のダメージを受けた\n");
}

void showBattleField(BattleField *pField)
{
    printf("------------------------------\n\n");
    printf("          ");
    printMonsterName(pField->pEnemy);
    printf("\n       HP= %4d / %4d\n", pField->pEnemy->hp, pField->pEnemy->maxhp);
    printf("\n\n");
    for (int i = 0; i < pField->pParty->numMonsters; i++)
    {
        printMonsterName(&(pField->pParty->monsters[i]));
        printf("  ");
    }
    printf("\n");
    printf("       HP= %4d / %4d\n", pField->pParty->hp, pField->pParty->maxHp);
    printf("------------------------------\n");
    printf(" ");
    for (int i = 0; i < MAX_GEMS; i++)
    {
        printf("%c ", 'A' + i);
    }
    printf("\n");
    printGems(pField->gems);
    printf("------------------------------\n");
}

void printMonsterName(Monster *pMonster)
{
    char symbol = ELEMENT_SYMBOLS[pMonster->element];

    printf("\x1b[3%dm", ELEMENT_COLORS[pMonster->element]);
    printf("%c%s%c", symbol, pMonster->name, symbol);
    printf("\x1b[0m");
}

void fillGems(Element *gems)
{
    for (int i = 0; i < MAX_GEMS; i++)
    {
        gems[i] = rand() % EMPTY;
    }
}

void printGems(Element *gems)
{
    for (int i = 0; i < MAX_GEMS; i++)
    {
        printf(" ");
        printGem(gems[i]);
    }
    printf("\n");
}

void printGem(Element e)
{
    printf("\x1b[30m");
    printf("\x1b[4%dm", ELEMENT_COLORS[e]);
    printf("%c", ELEMENT_SYMBOLS[e]);
    printf("\x1b[0m");
}
