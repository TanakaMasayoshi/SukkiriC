#include <stdio.h>

// 属性を表す列挙型（FIRE=0, WATER=1, ...）
typedef enum Element
{
    FIRE,
    WATER,
    WIND,
    EARTH,
    LIFE,
    EMPTY
} Element;

// 各属性に対応するシンボル文字
const char ELEMENT_SYMBOLS[EMPTY + 1] = {'$', '~', '@', '#', '&', ' '};

// 各属性に対応するANSIカラーコード（ターミナルの文字色変更用）
const char ELEMENT_COLORS[EMPTY + 1] = {1, 6, 2, 3, 5, 0};

// モンスター構造体の定義
typedef struct MONSTER
{
    char *name;      // モンスターの名前
    Element element; // 属性
    int maxhp;       // 最大HP
    int hp;          // 現在HP
    int attack;      // 攻撃力
    int defense;     // 防御力
} Monster;

// ダンジョン構造体の定義
typedef struct DUNGEON
{
    Monster *monsters;     // ダンジョン内のモンスター配列
    const int numMonsters; // モンスターの数
} Dungeon;

// プレイヤーのパーティ構造体
typedef struct PARTY
{
    char *playerName;  // プレイヤーの名前（文字列）
    Monster *monsters; // 所属するモンスター配列
    int numMonsters;   // モンスター数
    int maxhp;         // パーティ全体の最大HP（合計）
    int hp;            // パーティの現在HP
    int defense;       // パーティの防御力（平均）
} Party;

// 関数プロトタイプ宣言
int goDungeon(Party *pParty, Dungeon *pDungeon);
int doBattle(Party *pParty, Monster *pEnemy);
Party organizeParty(char *name, Monster *monsters, int numMonsters);
void showParty(Party *pParty);
void printMonsterName(Monster *monster);

// メイン関数：ゲームのスタート
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        // 引数が正しくないときエラー表示
        printf("エラー：プレイヤー名を入力してください\n");
        return 1;
    }

    printf("*** Puzzle & Monsters ***\n");

    // パーティに入るモンスターを定義
    Monster partyMonsters[] = {
        {"朱雀", FIRE, 150, 150, 25, 10},
        {"青龍", WATER, 130, 130, 20, 15},
        {"白虎", WIND, 140, 140, 22, 12},
        {"玄武", EARTH, 160, 160, 18, 20}};

    // パーティ作成（プレイヤー名とモンスターを指定）
    Party party = organizeParty(argv[1], partyMonsters, 4);

    // ダンジョンのモンスターを定義
    Monster dungeonMonster[] = {
        {"スライム", WATER, 100, 100, 10, 5},
        {"ゴブリン", EARTH, 200, 200, 20, 15},
        {"オオコウモリ", WIND, 300, 300, 30, 25},
        {"ウェアウルフ", WIND, 400, 400, 40, 30},
        {"ドラゴン", FIRE, 800, 800, 50, 40}};

    // ダンジョン作成
    Dungeon dungeon = {dungeonMonster, 5};

    // ダンジョンに突入し、倒した数を記録
    int victoryCount = goDungeon(&party, &dungeon);

    // クリア判定
    if (victoryCount == dungeon.numMonsters)
    {
        printf("ゲームクリア！\n");
    }
    else
    {
        printf("ゲームオーバー\n");
    }

    // 結果表示
    printf("倒したモンスターの数=%d\n", victoryCount);
    return 0;
}

// ダンジョン進行処理
int goDungeon(Party *pParty, Dungeon *pDungeon)
{
    // パーティ情報表示
    printf("%sのパーティ(HP=%d)はダンジョンに到着した\n", pParty->playerName, pParty->hp);
    showParty(pParty);

    int victoryCount = 0;
    // モンスターを順番に戦う
    for (int i = 0; i < pDungeon->numMonsters; i++)
    {
        victoryCount += doBattle(pParty, &(pDungeon->monsters[i]));

        // パーティが倒れたら終了
        if (pParty->hp <= 0)
        {
            printf("%sはダンジョンから逃げ出した...\n", pParty->playerName);
            break;
        }
        else
        {
            printf("%sはさらに奥へと進んだ\n\n", pParty->playerName);
            
        }
        printf("================\n\n");
    }

    return victoryCount;
}

// 戦闘処理（現在は必ず勝つ簡易版）
int doBattle(Party *pParty, Monster *pEnemy)
{
    printMonsterName(pEnemy);
    printf("が現れた！\n");

    // 実際のバトル処理はまだ未実装（常に勝利）
    printMonsterName(pEnemy);
    printf("を倒した！\n");

    return 1; // 勝ったときに1を返す
}

// パーティの情報をまとめて作成
Party organizeParty(char *playerName, Monster *monsters, int numMonsters)
{
    int sumHp = 0;
    int sumDefense = 0;

    // HPと防御の合計を計算
    for (int i = 0; i < numMonsters; i++)
    {
        sumHp += monsters[i].hp;
        sumDefense += monsters[i].defense;
    }

    int avgDefense = sumDefense / numMonsters;

    // パーティ構造体を初期化して返す
    Party p = {playerName, monsters, numMonsters, sumHp, sumHp, avgDefense};
    return p;
}

// パーティのモンスター一覧を表示
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

// モンスターの名前をカラー＆シンボル付きで表示
void printMonsterName(Monster *pMonster)
{
    char symbol = ELEMENT_SYMBOLS[pMonster->element];

    // 色の設定（ANSIエスケープシーケンス）
    printf("\x1b[3%dm", ELEMENT_COLORS[pMonster->element]);

    // シンボルと名前表示
    printf("%c%s%c", symbol, pMonster->name, symbol);

    // 色リセット
    printf("\x1b[0m");
}
