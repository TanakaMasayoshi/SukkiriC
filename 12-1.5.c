/*=== puzmon1hint: ゲーム全体の流れの実装 ===*/
/*** インクルード宣言 ***/

#include <stdio.h>

/*** 列挙型宣言 ***/

/*** グローバル定数の宣言 ***/

/*** 構造体型宣言 ***/

/*** プロトタイプ宣言 ***/

// HINT: goDungeon関数のプロトタイプ宣言

// HINT: doBattle関数のプロトタイプ宣言

/*** 関数宣言 ***/

// (1)ゲーム開始から終了までの流れ
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("エラー：プレイヤー名を入力してください\n");
        return 1;
    }

    const char *playerName = argv[1];
    printf("*** Puzzle & Monsters ***\n");

    // いざ、ダンジョンへ
    int victoryCount = goDungeon(playerName);

    // 冒険終了後
    if (victoryCount == 5)
    {
        printf("ゲームクリア！\n");
    }
    else
    {
        printf("ゲームオーバー\n");
    }

    // 倒したモンスター数を表示する
    printf("倒したモンスターの数:=%d\n", victoryCount);
    return 0;
}

// (2)ダンジョン開始から終了までの流れ
int goDungeon(const char *playerName)
{
    printf("%sはダンジョンに到着した\n", playerName);

    int victoryCount = 0;
    victoryCount += doBattle(playerName, "スライム");
    victoryCount += doBattle(playerName, "ゴブリン");
    victoryCount += doBattle(playerName, "オオコウモリ");
    victoryCount += doBattle(playerName, "ウェアウルフ");
    victoryCount += doBattle(playerName, "ドラゴン");

    printf("%sはダンジョンを制覇した！\n", playerName);
    return victoryCount;
}

// (3)バトル開始から終了までの流れ
int doBattle(const char *playerName, const char *monsterName)
{
    printf("%sが現れた！\n", monsterName);

    // （ダミー戦闘で即勝利確定）
    printf("%sを倒した！\n", monsterName);
    return 1; // 倒した敵の数（常に1）を返す
}

/*** ユーティリティ関数宣言 ***/
