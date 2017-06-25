/*
 * Problem Solving Assignment8-2 : 선분 그룹
 * https://www.acmicpc.net/problem/2162
 */

#include <cstdio>
#include <algorithm>
#define MAXLEN 3001
using namespace std;

struct Point {
    int x, y;
};

struct Line {
    Point p1, p2;
};

Line input[MAXLEN];
int cnt[MAXLEN];
int group[MAXLEN];

bool overlap(Point a, Point b, Point c) {
    return (min(a.x, b.x) <= c.x && c.x <= max(a.x, b.x) && min(a.y, b.y) <= c.y && c.y <= max(a.y, b.y));
}

int ccw(Point a, Point b, Point c) {
    int ret = a.x * b.y - a.y * b.x + b.x * c.y - c.x * b.y + c.x * a.y - a.x * c.y;
    if(ret > 0)
        return 1;
    else if(ret == 0)
        return 0;
    return -1;
}

bool is_intersection(Point p1, Point p2, Point p3, Point p4) {
    int ret1 = ccw(p1, p2, p3);
    int ret2 = ccw(p1, p2, p4);
    int ret3 = ccw(p3, p4, p1);
    int ret4 = ccw(p3, p4, p2);

    if (ret1 * ret2 < 0 && ret3 * ret4 < 0)
        return true;
    if (ret1 == 0 && overlap(p1, p2, p3))
        return true;
    if (ret2 == 0 && overlap(p1, p2, p4))
        return true;
    if (ret3 == 0 && overlap(p3, p4, p1))
        return true;
    return (ret4 == 0 && overlap(p3, p4, p2));
}

void init(int n) {
    for(int i = 1; i <= n; i++)
        group[i] = i;
}

int find(int i) {
    int j = i;
    while(group[j] != j)
        j = group[j];
    return j;
}

void merge(int i, int j)  {
    int p = find(i);
    if(group[j] == j)
        group[j] = p;
    else {
        int q = group[j];
        group[j] = p;
        group[q] = p;
    }
}

int main(void) {
    int N;
    scanf("%d", &N);

    for(int i = 1; i <= N; i++)
        scanf("%d %d %d %d", &input[i].p1.x, &input[i].p1.y, &input[i].p2.x, &input[i].p2.y);

    init(N);
    for(int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) {
            if(i == j)
                continue;
            if (is_intersection(input[i].p1, input[i].p2, input[j].p1, input[j].p2))
                merge(i, j);
        }

    int idx;
    for(int i = 1; i <= N; i++) {
        idx = find(i);
        cnt[idx]++;
    }

    int max_size = -1;
    int group_num = 0;
    for(int i = 1; i <= N; i++) {
        if(cnt[i] >= 1)
            group_num++;
        if(max_size < cnt[i])
            max_size = cnt[i];
    }

    printf("%d\n%d\n", group_num, max_size);
    return 0;
}