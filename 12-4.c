#include <stdio.h> // 入出力ライブラリのインクルード

// 属性の列挙型定義
typedef enum Element
{
    FIRE,  // 火属性
    WATER, // 水属性
    WIND,  // 風属性
    EARTH, // 土属性
    LIFE,  // 命（回復系？未使用）
    EMPTY  // 空（無属性）
} Element;

// 各属性に対応する記号（シンボル）
const char ELEMENT_SYMBOLS[EMPTY + 1] = {'$', '~', '@', '#', '&', ' '};

// 各属性に対応する色コード（ターミナル表示用）
const int ELEMENT_COLORS[EMPTY + 1] = {1, 6, 2, 3, 5, 0};

// モンスター構造体の定義
typedef struct MONSTER
{
    char *name;      // モンスターの名前
    Element element; // 属性
    int maxhp;       // 最大HP
    int hp;          // 現在のHP
    int attack;      // 攻撃力
    int defense;     // 防御力
} Monster;

// ダンジョン構造体の定義
typedef struct DUNGEON
{
    Monster *monsters; // 登場モンスターの配列
    int numMonsters;   // モンスター数
} Dungeon;

// パーティ構造体の定義
typedef struct PARTY
{
    char *playerName;  // プレイヤー名
    Monster *monsters; // 所属モンスターの配列
    int numMonsters;   // モンスター数
    int maxhp;         // パーティ全体の最大HP
    int hp;            // 現在HP
    int defense;       // 平均防御力
} Party;

// 関数プロトタイプ宣言（定義は後で）
int goDungeon(Party *pParty, Dungeon *pDungeon);
int doBattle(Party *pParty, Monster *pEnemy);
Party organizeParty(char *name, Monster *monsters, int numMonsters);
void showParty(Party *pParty);
void onPlayerTurn(Party *pParty, Monster *pEnemy);
void doAttack(Monster *pEnemy);
void onEnemyTurn(Party *pParty, Monster *pEnemy);
void doEnemyAttack(Party *pParty);
void printMonsterName(Monster *monster);

// メイン関数（プログラムのエントリーポイント）
int main(int argc, char **argv)
{
    // プレイヤー名が渡されていない場合はエラー
    if (argc != 2)
    {
        printf("エラー：プレイヤー名を入力してください\n");
        return 1;
    }

    printf("*** Puzzle & Monsters ***\n");

    // パーティ用のモンスター定義（初期値）
    Monster partyMonsters[] = {
        {"朱雀", FIRE, 150, 150, 25, 10},
        {"青龍", WATER, 130, 130, 20, 15},
        {"白虎", WIND, 140, 140, 22, 12},
        {"玄武", EARTH, 160, 160, 18, 20}};

    // パーティを編成
    Party party = organizeParty(argv[1], partyMonsters, 4);

    // ダンジョン内の敵モンスター定義
    Monster dungeonMonster[] = {
        {"スライム", WATER, 100, 100, 10, 5},
        {"ゴブリン", EARTH, 200, 200, 20, 15},
        {"オオコウモリ", WIND, 300, 300, 30, 25},
        {"ウェアウルフ", WIND, 400, 400, 40, 30},
        {"ドラゴン", FIRE, 800, 800, 50, 40}};

    // ダンジョン作成
    Dungeon dungeon = {dungeonMonster, 5};

    // ダンジョン攻略開始
    int victoryCount = goDungeon(&party, &dungeon);

    // ゲームの結果表示
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

// ダンジョン探索処理
int goDungeon(Party *pParty, Dungeon *pDungeon)
{
    // ダンジョン到着のメッセージ
    printf("%sのパーティ(HP=%d)はダンジョンに到着した\n", pParty->playerName, pParty->hp);
    showParty(pParty);

    int victoryCount = 0;
    // 各敵モンスターとバトルを実施
    for (int i = 0; i < pDungeon->numMonsters; i++)
    {
        victoryCount += doBattle(pParty, &(pDungeon->monsters[i]));
        if (pParty->hp <= 0)
        {
            // HPが0以下なら探索中断
            printf("%sはダンジョンから逃げ出した...\n", pParty->playerName);
            break;
        }
        else
        {
            // 続行メッセージ
            printf("%sはさらに奥へと進んだ\n\n", pParty->playerName);
            printf("================\n\n");
        }
    }
    return victoryCount;
}

// バトル処理
int doBattle(Party *pParty, Monster *pEnemy)
{
    printMonsterName(pEnemy);
    printf("が現れた！\n");

    // プレイヤーと敵がともに生きている間は戦闘継続
    while (pParty->hp > 0 && pEnemy->hp > 0)
    {
        onPlayerTurn(pParty, pEnemy);
        if (pEnemy->hp <= 0)
            break;

        onEnemyTurn(pParty, pEnemy);
        if (pParty->hp <= 0)
            break;
    }

    // 敵撃破時のメッセージ
    if (pEnemy->hp <= 0)
        printMonsterName(pEnemy);
    printf("を倒した！\n");
    return 1;
}

// パーティの編成（HPと防御を集計）
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

// パーティのステータスを表示
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

// 属性色付きでモンスター名を表示
void printMonsterName(Monster *pMonster)
{
    char symbol = ELEMENT_SYMBOLS[pMonster->element];

    printf("\x1b[3%dm", ELEMENT_COLORS[pMonster->element]); // 色を変更
    printf("%c%s%c", symbol, pMonster->name, symbol);       // シンボル付き名前表示
    printf("\x1b[0m");                                      // 色リセット
}

// プレイヤーターンの処理
void onPlayerTurn(Party *pParty, Monster *pEnemy)
{
    printf("\n【%sのターン】\n", pParty->playerName);
    doAttack(pEnemy); // 現状は固定ダメージ
}

// プレイヤーによる攻撃処理（固定ダメージ）
void doAttack(Monster *pEnemy)
{
    pEnemy->hp -= 80;
    printf("ダミー攻撃で80のダメージを与えた\n");
}

// 敵ターンの処理
void onEnemyTurn(Party *pParty, Monster *pEnemy)
{
    printf("\n【%sのターン】\n", pEnemy->name);
    doEnemyAttack(pParty); // 敵の攻撃処理
}

// 敵による攻撃処理（固定ダメージ）
void doEnemyAttack(Party *pParty)
{
    pParty->hp -= 20;

    printf("20のダメージを受けた\n");
}
