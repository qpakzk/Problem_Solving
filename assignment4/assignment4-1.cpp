/*
 * 문제해결 4주차 과제4-1 : 편집 거리
 * https://www.acmicpc.net/problem/7620
 */

#include <cstdio>
#include <cstring>

#define MAXLEN 17000
#define NORTH 0//00
#define NORTH_WEST_A 1//01
#define NORTH_WEST_B 2//10
#define WEST 3//11

char str1[MAXLEN];
char str2[MAXLEN];
char before[MAXLEN][4250];

int dp[MAXLEN + 1];
int dp_next[MAXLEN + 1];

void edit_distance(int L1, int L2) {
    int val;
    int min;
    int a, b;
    char c, temp;

    for(int j = 1; j <= L2; j++)
        dp[j] = j;

    for(int i = 1; i <= L1; i++) {
        dp_next[0] = i;
        for(int j = 1; j <= L2; j++) {
            a = (j - 1) / 4;
            b = (j - 1) % 4;
            if(b == 0)
                c = 6;
            else if(b == 1)
                c = 4;
            else if(b == 2)
                c = 2;
            else
                c = 0;

            temp = 0;
            val = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            min = dp[j - 1] + val;
            if(val == 0) {//c
                temp = (char) NORTH_WEST_A;
                temp <<= c;
                before[i - 1][a] |= temp;
            }
            else {//m
                temp = (char) NORTH_WEST_B;
                temp <<= c;
                before[i - 1][a] |= temp;
            }
            //d
            if(min > dp[j] + 1) {
                before[i - 1][a] ^= temp;
                min = dp[j] + 1;
                temp = (char) NORTH;
                temp <<= c;
                before[i - 1][a] |= temp;
            }

            //a
            if(min > dp_next[j - 1] + 1) {
                before[i - 1][a] ^= temp;
                min = dp_next[j - 1] + 1;
                temp = (char) WEST;
                temp <<= c;
                before[i - 1][a] |= temp;
            }

            dp_next[j] = min;
        }

        for(int j = 0; j <= L2; j++)
            dp[j] = dp_next[j];
    }
}


void search_path(int L1, int L2) {
    int a, b;
    char c, d, temp = 0;
    char north_west_a = (char) NORTH_WEST_A;
    char north_west_b = (char) NORTH_WEST_B;
    char north = (char) NORTH;
    char west = (char) WEST;
    if(L1 == 0 || L2 == 0) {
        if(L1 == 0 && L2 > 0)
            for(int i = 1; i <= L2; i++)
                printf("a %c\n", str2[i - 1]);

        if(L2 == 0 && L1 > 0)
            for(int i = 1; i <= L1; i++)
                printf("d %c\n", str1[i - 1]);
        return;
    }

    a = (L2 - 1) / 4;
    b = (L2 - 1) % 4;
    if (b == 0)
        c = 6;
    else if (b == 1)
        c = 4;
    else if (b == 2)
        c = 2;
    else
        c = 0;

    north_west_a <<= c;
    north_west_b <<= c;
    north <<= c;
    west <<= c;
    d = 3;
    d <<= c;
    temp = before[L1 - 1][a];
    temp &= d;
    if ((temp ^ north_west_a) == 0) {
        search_path(L1 - 1, L2 - 1);
        printf("c %c\n", str2[L2 - 1]);
    } else if ((temp ^ north_west_b) == 0) {
        search_path(L1 - 1, L2 - 1);
        printf("m %c\n", str2[L2 - 1]);
    } else if ((temp ^ north) == 0) {
        search_path(L1 - 1, L2);
        printf("d %c\n", str1[L1 - 1]);
    } else if ((temp ^ west) == 0) {
        search_path(L1, L2 - 1);
        printf("a %c\n", str2[L2 - 1]);
    }
}

int main(void) {
    scanf("%s", str1);
    scanf("%s", str2);

    int L1 = (int) strlen(str1);
    int L2 = (int) strlen(str2);

    edit_distance(L1, L2);
    search_path(L1, L2);

    return 0;
}