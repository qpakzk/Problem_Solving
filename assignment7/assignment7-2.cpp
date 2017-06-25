/*
 * Problem Solving Assignment7-2 : 여행 계획 세우기
 * https://www.acmicpc.net/problem/2152
 */

#include <cstdio>
#include <vector>
#include <stack>
#include <cstring>
#define MAXLEN 10001
using namespace std;

int N, M, S, T;
vector<vector<int> > G, GI, GG;
bool visited[MAXLEN];
int g_num, group[MAXLEN], g_cnt[MAXLEN], result[MAXLEN];
stack<int> s;

int max(int a, int b) {
    return a > b ? a : b;
}

void DFS(int v) {
    visited[v] = true;
    for(int i = 0; i < G[v].size(); i++)
        if(!visited[G[v][i]])
            DFS(G[v][i]);
    s.push(v);
}

void SCC(int v) {
    visited[v] = true;
    group[v] = g_num;
    g_cnt[g_num]++;
    for(int i = 0; i < GI[v].size(); i++)
        if(!visited[GI[v][i]])
            SCC(GI[v][i]);
}

void DFS2(int v, int weight) {
    result[v] = max(result[v], weight);

    for(int i = 0; i < GG[v].size(); i++) {
        if(result[v] + g_cnt[GG[v][i]] > result[GG[v][i]])
            DFS2(GG[v][i], g_cnt[GG[v][i]] + result[v]);
    }
    visited[v] = false;
}

int main(void) {
    scanf("%d %d %d %d", &N, &M, &S, &T);
    G.resize(N + 1);
    GI.resize(N + 1);

    for(int m = 1; m <= M; m++) {
        int A, B;
        scanf("%d %d", &A, &B);
        G[A].push_back(B);
        GI[B].push_back(A);
    }

    memset(visited, 0, sizeof(visited));
    for(int n = 1; n <= N; n++) {
        if (!visited[n])
            DFS(n);
    }

    memset(visited, 0, sizeof(visited));
    while(!s.empty()) {
        int v = s.top();
        s.pop();
        if(!visited[v]) {
            g_num++;
            SCC(v);
        }
    }

    GG.resize(g_num + 1);
    for (int i = 1; i <= N; i++)
        for(int j = 0; j < G[i].size(); j++)
            if (group[i] != group[G[i][j]])
                GG[group[i]].push_back(group[G[i][j]]);

    memset(visited, 0, sizeof(visited));
    DFS2(group[S], g_cnt[group[S]]);
    printf("%d\n", result[group[T]]);
    return 0;
}
