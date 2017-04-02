/*
 * 문제해결 4주차 과제4-2 : 전깃줄 - 2
 * https://www.acmicpc.net/problem/2568
 */

#include <cstdio>

#define MAX 600000
#define INF 1000000

int LIS[MAX];
int LIS_r[MAX];
int x[MAX];
int P[MAX];
int j;
int del_list[MAX];
int max_index = 0;

void binSearch(int low, int high, int target) {

    while(low <= high) {
        int mid = (low + high) / 2;
        if(LIS[mid] > target) {
            if(mid >= 1)
                high = mid - 1;
            else
                return;
        }
        else {
            j = mid;
            if(mid + 1 <= max_index)
                low = mid + 1;
            else
                return;
        }
    }
}

int main(void) {
    int N;
    scanf("%d", &N);

    LIS[0] = -INF;
    for(int i = 1; i < MAX; i++)
        LIS[i] = INF;

    for(int i = 0; i < N; i++) {
        int index;
        int val;
        scanf("%d%d", &index, &val);
        if(max_index == 0 || max_index < index)
            max_index = index;
        x[index] = val;
    }

    int L = 0;
    for(int i = 1; i <= max_index; i++) {
        if(x[i] == 0)
            continue;
        binSearch(0, max_index, x[i]);

        P[i] = j + 1;

        if(j == L || (j <= max_index && x[i] < LIS[j + 1])) {
            LIS[j + 1] = x[i];
            if(L < j + 1)
                L = j + 1;
        }
    }

    int temp = L;
    int s = 1, q = 1;
    for(int i = max_index; i >= 1; i--) {
        if(P[i] == 0)
            continue;
        if(P[i] == temp) {
            LIS_r[s] = x[i];
            s++;
            temp--;
        }
        else {
            del_list[q] = i;
            q++;
        }
    }

    printf("%d\n", N - L);
    for(int i = N - L; i >= 1; i--)
        printf("%d\n", del_list[i]);

    return 0;
}