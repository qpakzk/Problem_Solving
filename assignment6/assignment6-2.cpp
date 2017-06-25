/*
 * Problem Solving Assignment6-2
 * https://www.acmicpc.net/problem/1513
 */

#include <cstdio>
#define MAXLEN 51

int dp[MAXLEN][MAXLEN][MAXLEN][MAXLEN];
int city[MAXLEN][MAXLEN];

int main(void) {
    int N, M, C;
    int loc[MAXLEN][2];

    scanf("%d%d%d", &N, &M, &C);
    for(int c = 1; c <= C; c++)
        scanf("%d%d", &loc[c][0], &loc[c][1]);
    for(int c = 1; c <= C; c++)
        city[loc[c][0]][loc[c][1]] = c;

    if(city[1][1] == 0)
        dp[1][1][0][0] = 1;
    else
        dp[1][1][1][city[1][1]] = 1;

    for(int n = 1; n <= N; n++)
        for (int m = 1; m <= M; m++) {
            if(m == 1 && n == 1)
                continue;
            if (city[n][m] == 0)
                dp[n][m][0][0] = (dp[n - 1][m][0][0] + dp[n][m - 1][0][0]) % 1000007;
        }

    for(int n = 1; n <= N; n++)
        for(int m = 1; m <= M; m++) {
            if(m == 1 && n == 1)
                continue;
            if (city[n][m] == 0)
                for (int v = 1; v <= C; v++)
                    dp[n][m][1][v] = (dp[n][m][1][v] + dp[n - 1][m][1][v] + dp[n][m - 1][1][v]) % 1000007;
            else
                dp[n][m][1][city[n][m]] = (dp[n][m][1][city[n][m]] + dp[n - 1][m][0][0] + dp[n][m - 1][0][0]) % 1000007;
        }

    for(int n = 1; n <= N; n++)
        for(int m = 1; m <= M; m++) {
            if(m == 1 && n == 1)
                continue;
            for (int c = 2; c <= C; c++)
                if (city[n][m] == 0)
                    for (int v = 1; v <= C; v++)
                        dp[n][m][c][v] = (dp[n][m][c][v] + dp[n - 1][m][c][v] + dp[n][m - 1][c][v]) % 1000007;
                else
                    for (int v = 1; v < city[n][m]; v++)
                        dp[n][m][c][city[n][m]] =
                                (dp[n][m][c][city[n][m]] + dp[n - 1][m][c - 1][v] + dp[n][m - 1][c - 1][v]) % 1000007;
        }

    printf("%d ", dp[N][M][0][0]);
    for(int c = 1; c <= C; c++) {
        int result = 0;
        for(int v = 1; v <= C; v++)
            result = (result + dp[N][M][c][v]) % 1000007;
        printf("%d ", result % 1000007);
    }

    return 0;
}