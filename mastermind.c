#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void make4digits(int x[], int len) {
    int i, j, val;

    for (i = 0; i < len; i++) {
        do{
            val = rand() % 10;
            for (j = 0; j < i; j++) {
                if (val == x[j]) break;
            }
        } while (j < i);
        x[i] = val;
    }

#if DEBUG==1
    printf("answer: %d%d%d%d\n", x[0], x[1], x[2], x[3]);
#endif // DEBUG==1
}

int check(const char s[], const int len) {
    int i, j;

    if (strlen(s) != len)
        return 1;
    
    for(i = 0; i < len; i++) {
        if (!isdigit(s[i]))
            return 2;
        for(j = 0; j < i; j++)
            if (s[i] == s[j])
                return 3;
    }

    return 0;
}

void judge(const char s[], const int no[], const int len, int *hit, int *blow) {
    int i, j;

    *hit = *blow = 0;

    for(i = 0; i < len; i++) {
        for (j = 0; j < len; j++) {
            if (s[i] == '0' + no[j])
                if (i == j)
                    (*hit)++;
                else
                    (*blow)++;
        }
    }
}

void print_result(int snum, int spos, int len) {
    if (spos == len)
        printf("正解です！");
    else if (snum == 0)
        printf("    それらの数字は全く含まれません。\n");
    else {
        printf("    それらの数字中%d個の数字が含まれます。\n", snum);

        if (spos == 0)
            printf("    ただし位置もあっている数字はありません。\n");
        else 
            printf("    その中の%d個は位置はあっています。\n", spos);
    }
    putchar('\n');
}

int main(void) {
    int try_no = 0;
    int max_try_no = 5;
    int chk;
    int hit;
    int blow;
    int no[4];
    int no_len;
    char buff[10];
    clock_t start, end;

    srand(time(NULL));

    puts("■ マスターマインドをしましょう。");
    puts("■ 同じ数字が複数含まれることはありません。");
    puts("■ 4370のように連続して入力してください");
    while (1) {
        printf("■ 入力できる回数は何回にしますか。(1~20)：");
        scanf("%d", &max_try_no);
        if (max_try_no <= 0 || max_try_no > 20) {
            puts("1~20の数値を入力してください。");
            continue;
        } else {
            break;
        }
    }
    while (1) {
        printf("■ 答えは何桁の数にしますか。(1~10)：");
        scanf("%d", &no_len);
        if (no_len <= 0 || no_len >= 10) {
            puts("1~10の数値を入力してください。");
            continue;
        } else {
            printf("\n");
            break;
        }
    }
    make4digits(no, no_len);

    start = time(NULL);

    do {
        do {
            if (try_no > (max_try_no / 2)) printf("ヒント： 最初の数は%d\n", no[0]);
            printf("入力してください：");
            scanf("%s", buff);

            chk = check(buff, no_len);

            switch (chk) {
                case 1: puts("きちんと4文字で入力してください。"); break;
                case 2: puts("数字以外の文字を入力しないでください。"); break;
                case 3: puts("同一の数字を複数入力しないでください。"); break;
            }
        } while (chk != 0);

        try_no++;
        judge(buff, no, no_len, &hit, &blow);
        print_result(hit + blow, hit, no_len);
#if DEBUG==1
        printf("try_no: %d\n", try_no);
        printf("hit: %d\n", hit);
        printf("blow: %d\n", blow);
#endif // DEBUG==1
    } while (try_no < max_try_no && hit < no_len);

    end = time(NULL);

    if (hit == no_len) {
        printf("%d回かかりました。\n所要時間は%ld秒でした。\n", 
               try_no, end - start);
    } else {
        printf("%d回以内に正解できませんでした。\n正解は", max_try_no);
        for (int i = 0; i < no_len; i++) {
            printf("%d", no[i]);
        }
        printf("です。\n所要時間は%ld秒でした。\n", end - start);
    }
    

    return 0;
}