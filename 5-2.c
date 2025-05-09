#include <stdio.h>
#include <stdlib.h>

typedef char String[1024];

int main(void)
{
    String num1;
    printf("何月ですか？ :");
    scanf("%s",num1);
    int season = atoi(num1);

    switch (season){
      case 4 :
      case 5 :
      case 3 :
        printf("%s月は春です",num1);
        break;
      case 6 :
      case 7 :
      case 8 :
        printf("%s月は夏です",num1);
        break;
      case 9 :
      case 10 :
      case 11 :
        printf("%s月は秋です",num1);
        break;
      case 12 :
      case 1 :
      case 2 :
        printf("%s月は冬です",num1);
        break;
      default:
      printf("存在しない月です");
    }
    return 0;
}