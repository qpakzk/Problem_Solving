#include <stdio.h>
#include <string.h>

#define MAXLEN 10000

char X[MAXLEN];
char Y[MAXLEN];

int d[MAXLEN][MAXLEN];

void editDistance(int m, int n) {
    int val;
    int min;
    for(int i = 1; i <= m; i++)
        d[i][0] = i;
    for(int j = 1; j <= n; j++)
        d[0][j] = j;

    for(int i = 1; i <= m; i++) {
        for(int j= 1; j <=n; j++) {
            val = X[i - 1] == Y[j - 1] ? 0 : 1;
            min = d[i - 1][j - 1] + val;
            if(min > d[i - 1][j] + 1)
                min = d[i - 1][j] + 1;
            if(min > d[i][j - 1] + 1)
                min = d[i][j - 1] + 1;
            d[i][j] = min;
        }
    }
}

int main(void) {
    scanf("%s", X);
    scanf("%s", Y);
    int m = (int) strlen(X);
    int n = (int) strlen(Y);

    editDistance(m, n);

    for(int i = 0; i <= m; i++) {
        for(int j = 0; j <= n; j++)
            printf("%d ", d[i][j]);
        printf("\n");
    }

    printf("minimum number of edit operation : %d\n", d[m - 1][n - 1]);

    return 0;
}
