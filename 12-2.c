#include <stdio.h> // 標準入出力を使うためのヘッダ

// モンスターの属性（列挙型）
typedef enum Element
{
    FIRE,  // 火
    WATER, // 水
    WIND,  // 風
    EARTH, // 土
    LIFE,  // 命（回復など）
    EMPTY  // 無属性（空）
} Element;

// 属性に対応した記号を定義（モンスター名の装飾用）
const char ELEMENT_SYMBOLS[EMPTY + 1] = {'$', '~', '@', '#', '&', ' '};

// 属性に対応した色番号を定義（ANSIカラーコード：3X）
const char ELEMENT_COLORS[EMPTY + 1] = {1, 6, 2, 3, 5, 0};

// モンスター構造体の定義
typedef struct MONSTER
{
    char *name;      // モンスターの名前
    Element element; // 属性（火、水など）
    int maxhp;       // 最大HP
    int hp;          // 現在のHP
    int attack;      // 攻撃力
    int defense;     // 防御力
} Monster;

// ダンジョン構造体：モンスターの配列とその数
typedef struct DUNGEON
{
    Monster *monsters;     // モンスター配列へのポインタ
    const int numMonsters; // モンスター数（変更不可）
} Dungeon;

// 関数プロトタイプ宣言
int goDungeon(char *playerName, Dungeon *pDungeon); // ダンジョンに挑戦
int doBattle(char *playerName, Monster *pEnemy);    // モンスターとの戦闘
void printMonsterName(Monster *monster);            // モンスター名を色付きで表示

int main(int argc, char **argv)
{
    // コマンドライン引数のチェック（プレイヤー名が必要）
    if (argc != 2)
    {
        printf("エラー：プレイヤー名を入力してください\n");
        return 1;
    }

    printf("*** Puzzle & Monsters ***\n"); // タイトル表示

    // モンスターの定義（初期状態）
    Monster dungeonMonster[] = {
        {"スライム", WATER, 100, 100, 10, 5},
        {"ゴブリン", EARTH, 200, 200, 20, 15},
        {"オオコウモリ", WIND, 300, 300, 30, 25},
        {"ウェアウルフ", WIND, 400, 400, 40, 30},
        {"ドラゴン", FIRE, 800, 800, 50, 40}};

    // ダンジョンにモンスターを登録
    Dungeon dungeon = {dungeonMonster, 5};

    // ダンジョンを進行（バトルを開始）
    int victoryCount = goDungeon(argv[1], &dungeon);

    // クリア判定（全て倒したか）
    if (victoryCount == dungeon.numMonsters)
    {
        printf("ゲームクリア！\n");
    }
    else
    {
        printf("ゲームオーバー\n");
    }

    // 勝利したモンスター数の表示
    printf("倒したモンスターの数=%d\n", victoryCount);
    return 0;
}

// ダンジョンを進む処理
int goDungeon(char *playerName, Dungeon *pDungeon)
{
    printf("%sはダンジョンに到着した\n", playerName);

    int victoryCount = 0; // 倒したモンスター数の初期化

    // モンスターの数だけバトルを繰り返す
    for (int i = 0; i < pDungeon->numMonsters; i++)
    {
        // doBattle の戻り値を victoryCount に加算（1:勝利, 0:敗北）
        victoryCount += doBattle(playerName, &(pDungeon->monsters[i]));
    }

    printf("%sはダンジョンを制覇した！\n", playerName);
    return victoryCount;
}

// モンスターとの戦闘処理（現状では演出だけ）
int doBattle(char *playerName, Monster *pEnemy)
{
    printMonsterName(pEnemy); // モンスター名を色付きで表示
    printf("が現れた！\n");

    printMonsterName(pEnemy); // 同じく表示（演出）
    printf("を倒した！\n");

    return 1; // 勝利（今は必ず勝つようになっている）
}

// モンスター名を属性記号と色で表示
void printMonsterName(Monster *pMonster)
{
    char symbol = ELEMENT_SYMBOLS[pMonster->element]; // 属性記号を取得

    // 色設定（3X 形式のANSIカラーコードで前景色指定）
    printf("\x1b[3%dm", ELEMENT_COLORS[pMonster->element]);

    // 記号 + 名前 + 記号 で表示
    printf("%c%s%c", symbol, pMonster->name, symbol);

    // 色リセット
    printf("\x1b[0m");
}
