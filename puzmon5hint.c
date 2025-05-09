// (a)属性の定義
typedef enum Element {
    FIRE,    // 火属性
    WATER,   // 水属性
    WIND,    // 風属性
    EARTH,   // 土属性
    LIFE,    // 生命属性
    EMPTY    // 空属性（宝石がない状態）
  } Element;
  
  // (b)属性ごとの記号（画面に表示するシンボル）
  const char ELEMENT_SYMBOLS[EMPTY + 1] = {'$', '~', '@', '#', '&', ' '};
  
  // (c)属性ごとのカラーコード（ディスプレイ制御シーケンス用）
  const char ELEMENT_COLORS[EMPTY + 1] = {1, 6, 2, 3, 5, 0};
  
  // (d) バトルフィールドに並ぶ宝石の数を定義
  enum { MAX_GEMS = 14 };  // 最大14個の宝石スロット
  
  // (f) モンスターの構造体
  typedef struct MONSTER {
    char* name;
    Element element;
    int maxhp;
    int hp;
    int attack;
    int defense;
  } Monster;
  
  // (g) ダンジョンの構造体
  typedef struct DUNGEON {
    Monster* monsters;
    const int numMonsters;
  } Dungeon;
  
  // (h) パーティの構造体
  typedef struct PARTY {
    char* playerName;
    Monster* monsters;
    const int numMonsters;
    const int maxHp;
    int hp;
    const int defense;
  } Party;
  
  // (i) バトルフィールドの構造体（ターンごとの戦闘情報）
  typedef struct BATTLE_FIELD {
    Party* pParty;
    Monster* pEnemy;
    Element gems[MAX_GEMS];  // 宝石スロット
  } BattleField;
  
  // (1)ゲームの開始から終了までの流れ
  int main(int argc, char** argv) {
    srand((unsigned)time(NULL));  // 乱数の初期化
  
    if(argc != 2) {
      printf("エラー: プレイヤー名を指定して起動してください\n");
      return 1;
    }
  
    printf("*** Puzzle & Monsters ***\n");
  
    // パーティの編成
    Monster partyMonsters[] = {
      {"朱雀", FIRE,  150, 150, 25, 10},
      {"青龍", WIND,  150, 150, 15, 10},
      {"白虎", EARTH, 150, 150, 20,  5},
      {"玄武", WATER, 150, 150, 20, 15}
    };
    Party party = organizeParty(argv[1], partyMonsters, 4);
  
    // ダンジョンの設定
    Monster dungeonMonsters[] = {
      {"スライム",    WATER, 100, 100, 10,  5},
      {"ゴブリン",    EARTH, 200, 200, 20, 15},
      {"オオコウモリ", WIND,  300, 300, 30, 25},
      {"ウェアウルフ", WIND,  400, 400, 40, 30},
      {"ドラゴン",    FIRE,  800, 800, 50, 40}
    };
    Dungeon dungeon = {dungeonMonsters, 5};
  
    // ダンジョン探索開始
    int winCount = goDungeon(&party, &dungeon);
  
    // 結果表示
    if(winCount == dungeon.numMonsters) {
      printf("***GAME CLEAR!***\n");
    } else {
      printf("***GAME OVER***\n");
    }
    printf("倒したモンスター数＝%d\n", winCount);
    return 0;
  }
  
  // (3)バトル開始から終了までの流れ
  int doBattle(Party* pParty, Monster* pEnemy) {
    printMonsterName(pEnemy);  // モンスター名の表示
    printf("が現れた！\n");
  
    // バトルフィールドの初期化
    BattleField field = {pParty, pEnemy};
    fillGems(field.gems);  // 宝石の埋め込み
  
    while(true) {
      onPlayerTurn(&field);  // プレイヤーのターン
      if(pEnemy->hp <= 0) {  // 勝利判定
        printMonsterName(pEnemy);
        printf("を倒した！\n");
        return 1;
      }
  
      onEnemyTurn(&field);   // モンスターのターン
      if(pParty->hp <= 0) {  // 敗北判定
        printf("%sは倒れた...\n", pParty->playerName);
        return 0;
      }
    }
  }
  
  // (B)スロットにランダムな宝石で埋める
  void fillGems(Element* gems) {
    for(int i = 0; i < MAX_GEMS; i++) {
      gems[i] = rand() % EMPTY;  // 宝石をランダムに選択
    }
  }
  
  // (C)スロットに並ぶ宝石を表示する
  void printGems(Element* gems) {
    for(int i = 0; i < MAX_GEMS; i++) {
      printf(" ");
      printGem(gems[i]);
    }
    printf("\n");
  }
  
  // (D)1個の宝石の表示
  void printGem(Element e) {
    printf("\x1b[30m");       // 黒文字
    printf("\x1b[4%dm", ELEMENT_COLORS[e]); // 属性に基づく色背景
    printf("%c", ELEMENT_SYMBOLS[e]);
    printf("\x1b[0m");        // 色解除
  }
  
  // (6)プレイヤーターンの処理
  void onPlayerTurn(BattleField* pField) {
    printf("\n【%sのターン】\n", pField->pParty->playerName);
    showBattleField(pField);  // バトルフィールドの表示
    doAttack(pField);         // 攻撃処理
  }
  
  // (7)攻撃処理（ダミー）
  void doAttack(BattleField* pField) {
    pField->pEnemy->hp -= 80;  // ダミー攻撃で80のダメージ
    printf("ダミー攻撃で80のダメージを与えた\n");
  }
  
  // (8)敵モンスターターン
  void onEnemyTurn(BattleField* pField) {
    printf("\n【%sのターン】\n", pField->pEnemy->name);
    doEnemyAttack(pField);  // 敵の攻撃処理
  }
  
  // (9)敵モンスターの攻撃
  void doEnemyAttack(BattleField* pField) {
    pField->pParty->hp -= 20;  // ダミーの攻撃で20のダメージ
    printf("20のダメージを受けた\n");
  }
  
  
  // (10)バトルフィールドの表示
  void showBattleField(BattleField* pField) {
    printf("------------------------------\n\n");
    printf("          ");
    printMonsterName(pField->pEnemy);  // 敵のモンスター名
    printf("\n       HP= %4d / %4d\n", pField->pEnemy->hp, pField->pEnemy->maxhp);
    printf("\n\n");
  
    // パーティメンバーの表示
    for(int i = 0; i < pField->pParty->numMonsters; i++) {
      printMonsterName(&(pField->pParty->monsters[i]));
      printf("  ");
    }
    printf("\n");
    printf("       HP= %4d / %4d\n", pField->pParty->hp, pField->pParty->maxHp);
    printf("------------------------------\n");
  
    // 宝石スロット表示
    printf(" ");
    for(int i = 0; i < MAX_GEMS; i++) {
      printf("%c ", 'A' + i);  // A～Nの表示
    }
    printf("\n");
    printGems(pField->gems);  // 宝石の表示
    printf("------------------------------\n");
  }
  