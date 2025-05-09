#include <stdio.h>

int main()
{
    // 背景色を黒に
    printf("\x1b[40m黒\n");
    // 背景色を赤に
    printf("\x1b[41m赤\n");
    // 背景色を緑に
    printf("\x1b[42m緑\n");
    // 背景色を黄色に
    printf("\x1b[43m黄色\n");
    // 背景色を青に
    printf("\x1b[44m青\n");
    // 背景色をマゼンタに
    printf("\x1b[45mマゼンタ\n");
    // 背景色をシアンに
    printf("\x1b[46mシアン\n");
    // 背景色を灰色に
    printf("\x1b[47m灰色\n");
    // 背景色をデフォルトに戻す
    printf("\x1b[49mリセット\n");

    // 前景色を黒に
    printf("\x1b[30m黒\n");
    // 前景色を赤に
    printf("\x1b[31m赤\n");
    // 前景色を緑に
    printf("\x1b[32m緑\n");
    // 前景色を黄色に
    printf("\x1b[33m黄色\n");
    // 前景色を青に
    printf("\x1b[34m青\n");
    // 前景色をマゼンタに
    printf("\x1b[35mマゼンタ\n");
    // 前景色をシアンに
    printf("\x1b[36mシアン\n");
    // 前景色を灰色に
    printf("\x1b[37m灰色\n");
    // 前景色をデフォルトに戻す
    printf("\x1b[39mリセット\n");
}
