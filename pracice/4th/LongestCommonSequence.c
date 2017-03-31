#include <stdio.h>
#include <string.h>
#define MAXLEN 10000
#define NORTH 0
#define NORTH_WEST 1
#define WEST 2

char X[MAXLEN];
char Y[MAXLEN];

int c[MAXLEN][MAXLEN];
int b[MAXLEN][MAXLEN];
char LCS[MAXLEN] = {0};
int idx = 0;

void LCS_len(int m, int n) {
    for(int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1] + 1;
                b[i][j] = NORTH_WEST;
            }
            else {
                if (c[i - 1][j] >= c[i][j - 1]) {
                    c[i][j] = c[i - 1][j];
                    b[i][j] = NORTH;
                }
                else {
                    c[i][j] = c[i][j - 1];
                    b[i][j] = WEST;
                }
            }
        }
    }
}

void print_LCS(int i, int j) {
    if(i == 0 || j == 0)
        return;

    if(b[i][j] == NORTH_WEST) {
        print_LCS(i - 1, j - 1);
        LCS[idx] = X[i - 1];
        idx++;
    }
    else if(b[i][j] == NORTH)
        print_LCS(i - 1, j);
    else if(b[i][j] == WEST)
        print_LCS(i, j - 1);

}
int main(void) {
    scanf("%s", X);
    scanf("%s", Y);

    int m = (int) strlen(X);
    int n = (int) strlen(Y);

    LCS_len(m, n);

    print_LCS(m, n);
    printf("[Longest Common Sequence] Length = %d\n", c[m][n]);
    printf("[Longest Common Sequence] : ");
    for(int i = idx - 1; i >= 0; i--)
        printf("%c", LCS[i]);
    printf("\n");
    return 0;
}
