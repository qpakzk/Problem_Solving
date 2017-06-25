/*
 * 문제해결 5주차 과제5-1 : 사과와 바나나
 * https://www.acmicpc.net/problem/3114
 */

#include <cstdio>
#include <cstring>
#define MAXLEN 1501

struct Land {
    char tree;
    int num;
};

int R, C;
Land land[MAXLEN][MAXLEN];
int psum_A[MAXLEN][MAXLEN];
int psum_B[MAXLEN][MAXLEN];
int dp[MAXLEN][MAXLEN];

int max_val(int v1, int v2, int v3) {
    int max = v1;
    if(v2 > max)
        max = v2;
    if(v3 > max)
        max = v3;
    return max;
}

int main(void) {
    scanf("%d%d", &R, &C);

    for(int r = 1; r <= R; r++)
        for (int c = 1; c <= C; c++)
            scanf(" %c%d", &land[r][c].tree, &land[r][c].num);

    for(int c = 1; c <= C; c++) {
        psum_A[1][c] = 0;
        if(land[1][c].tree == 'A')
            psum_A[1][c] += land[1][c].num;
        for(int r = 2; r <= R; r++) {
            psum_A[r][c] = psum_A[r - 1][c];
            if(land[r][c].tree == 'A')
                psum_A[r][c] += land[r][c].num;
        }
    }

    for(int c = 1; c <= C; c++) {
        psum_B[1][c] = 0;
        if(land[1][c].tree == 'B')
            psum_B[1][c] += land[1][c].num;
        for(int r = 2; r <= R; r++) {
            psum_B[r][c] = psum_B[r - 1][c];
            if(land[r][c].tree == 'B')
                psum_B[r][c] += land[r][c].num;
        }
    }
/*
    printf("psum_A\n");
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++)
            printf("%d ", psum_A[r][c]);
        printf("\n");
    }
    printf("\n");

    printf("psum_B\n");
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++)
            printf("%d ", psum_B[r][c]);
        printf("\n");
    }
    printf("\n");
*/
    dp[1][1] = psum_A[R][1] - psum_A[1][1];
    for(int c = 2; c <= C; c++) {
        dp[1][c] = dp[1][c - 1];
        dp[1][c] += (psum_A[R][c] - psum_A[1][c]);
    }
    for(int r = 2; r <= R; r++) {
        dp[r][1] = dp[r - 1][1];
        if(land[r][1].tree == 'A')
            dp[r][1] -= land[r][1].num;
    }

    int val1, val2, val3;
    for(int r = 2; r <= R; r++) {
        for(int c = 2; c <= C; c++) {
            //왼쪽에서 오른쪽
            val1 = dp[r][c - 1] + psum_B[r - 1][c] + (psum_A[R][c] - psum_A[r][c]);
            //대각선으로
            val2 = dp[r - 1][c - 1] + psum_B[r - 1][c] + (psum_A[R][c] - psum_A[r][c]);
            //아래로
            val3 = dp[r - 1][c];
            //printf("val1 : %d, val2 : %d, val3 : %d\n", val1, val2, val3);
            if(land[r][c].tree == 'A')
                val3 -= land[r][c].num;
            dp[r][c] = max_val(val1, val2, val3);
        }
    }
/*
    printf("dp\n");
    for(int r = 1; r <= R; r++) {
        for(int c = 1; c <= C; c++)
            printf("%d ", dp[r][c]);
        printf("\n");
    }
    printf("\n");
*/
    printf("%d\n", dp[R][C]);
    return 0;
}