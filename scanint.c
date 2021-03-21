#include <stdio.h>

int main(void) {
    int x;      // readed val

    printf("整数を入力してください：");
    scanf("%d", &x);

    printf("%dと入力しましたね。\n", x);

    return 0;
}