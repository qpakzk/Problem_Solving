#include <stdio.h>
#include <string.h>

#define MAXLEN 10000

int X[MAXLEN];
int L[MAXLEN];

void LIS(int n) {
    for(int i = 1; i <= n; i++) {
        L[i] = 1;

        for(int j = 1; j <= i - 1; j++)
            if (X[j] <= X[i] && L[j] + 1 > L[i])
                L[i] = L[j] + 1;
    }
}

void RecoverHelper(int k) {
    if(k > 0) {

    }
}
int main(void) {
    int N;
    scanf("%d", &N);

    for(int i = 1; i <= N; i++)
        scanf("%d", &X[i]);

    LIS(N);

    printf("Longest Increasing Sequence : %d\n", L[N]);

    return 0;
}
