/*
 * 문제해결 2주차 과제2-3 : 버블 소트
 * https://www.acmicpc.net/problem/1377
 */

#include <cstdio>
#include <cstdlib>

struct Value {
    int number;
    int pos;
};

int comp(const void *a, const void *b) {
    Value *n1 = (Value *)a;
    Value *n2 = (Value *)b;

    if(n1->number < n2->number)
        return -1;
    else if(n1->number == n2->number)
        return 0;
    else
        return 1;
}

int main(void) {
    int N;
    scanf("%d", &N);

    Value A[N];
    for(int i = 0; i < N; i++) {
        scanf("%d", &A[i].number);
        A[i].pos = i;
    }

    bool isIncreasing = true;
    for(int i = 0; i < N - 1; i++)
        if(A[i].number > A[i + 1].number) {
            isIncreasing = false;
            break;
        }

    if(isIncreasing) {
        printf("1\n");
        exit(0);
    }

    qsort(A, N, sizeof(Value), comp);

    int max = 0;
    int gap = 0;
    for(int i = 0; i < N; i++) {
        gap = A[i].pos - i;
        if(max < gap)
            max = gap;
    }

    printf("%d\n", max + 1);
    return 0;
}