/*
 * 문제해결 2주차 과제2-1: Moo 게임
 * https://www.acmicpc.net/problem/5904
 */

#include <cstdio>
int result;//1 : m, 0 : o

void Moo(int N, int len, int k) {
    if(k == 0) {
        if(N == 1)
            result = 1;
        else
            result = 0;
        return;
    }

    int prev_len = (len - k - 3) / 2;
    int prev_N = N - prev_len;
    if(prev_N >= 1 && prev_N <= k + 3) {
        if(prev_N == 1)
            result = 1;
        else
            result = 0;
        return;
    }
    else if(prev_N < 1)
        Moo(N, prev_len, k - 1);
    else
        Moo(prev_N - (k + 3), prev_len, k - 1);
}

int main(void) {
    int N;
    scanf("%d", &N);

    int k = 0;
    int len = 3;
    while(len < N) {
        k++;
        len = 2 * len + k + 3;
    }

    //printf("k: %d\nlen: %d\n", k, len);
    Moo(N, len, k);

    if(result == 1)
        printf("m\n");
    else
        printf("o\n");

    return 0;
}