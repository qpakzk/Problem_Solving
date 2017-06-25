#include <cstdio>
#define MAXLEN 500
int dx[4] = {-1,  0, 1, 0};
int dy[4] = { 0, -1, 0, 1};
int dp[MAXLEN][MAXLEN];
int n;
int forest[MAXLEN][MAXLEN];

int max(int a, int b) {
    if(a > b)
        return a;
    else
        return b;
}

int Route(int x, int y) {
    if(dp[x][y] == 1) {
        for(int i = 0; i < 4; i++) {
            int Xidx = x + dx[i], Yidx = y + dy[i];
            if(Xidx >= n || Xidx < 0 || Yidx >= n || Yidx < 0)
                continue;
            if(forest[x][y] <= forest[Xidx][Yidx]) {
                continue;
            }
            dp[x][y] = max(dp[x][y], Route(Xidx, Yidx) + 1);
        }
    }
    return dp[x][y];
}

int main(void) {
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            scanf("%d", &forest[i][j]);
            dp[i][j] = 1;
        }
    }

    int largest = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            largest = max(Route(i, j), largest);

    printf("%d\n", largest);

    return 0;
}