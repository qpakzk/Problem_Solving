/*
 * Problem Solving Assignment11-1 : Job Postings
 * https://www.acmicpc.net/problem/7154
 */

#include <cstdio>
#include <vector>
#include <queue>
#include <climits>
#include <cstring>
#define INF INT_MAX
#define MAX 212
using namespace std;

int N, M;
int source, sink;
vector<int> graph[MAX];
int capacity[MAX][MAX], cost[MAX][MAX], flow[MAX][MAX], parent[MAX];

int satisfaction[3][4] = {
        {4, 3, 2, 1},
        {8, 7, 6, 5},
        {12, 11, 10, 9}
};

void add_edge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
}

bool input() {
    scanf("%d %d", &N, &M);
    if(N == 0 && M == 0)
        return true;

    for(int i = 0; i < MAX; i++)
        graph[i].clear();

    memset(cost, 0, sizeof(cost));
    memset(capacity, 0, sizeof(capacity));
    memset(flow, 0, sizeof(flow));

    source = 0;
    sink = N + M + 1;

    for(int i = 1; i <= N; i++) {
        int P;
        scanf("%d", &P);
        capacity[i][sink] = P;
        add_edge(i, sink);
    }

    for(int i = 1; i <= M; i++) {
        int y;
        scanf("%d", &y);
        capacity[source][i + N] = 1;
        add_edge(source, i + N);

        for(int j = 0; j < 4; j++){
            int c;
            scanf("%d", &c);
            capacity[i + N][c + 1] = 1;
            cost[c + 1][i + N] = satisfaction[y - 1][j];
            cost[i + N][c + 1] = -cost[c + 1][i + N];
            add_edge(i + N, c + 1);
        }
    }

    return false;
}

bool SPFA(void) {
    int d[MAX];
    bool inQ[MAX];
    for(int i = 0; i < MAX; i++) {
        d[i] = INF;
        inQ[i] = false;
    }

    d[source] = 0;

    queue<int> Q;
    Q.push(source);
    inQ[source] = true;

    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        inQ[u] = false;

        for(int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i];
            if((capacity[u][v] - flow[u][v]) > 0 && d[v] > d[u] + cost[u][v]){
                d[v] = d[u] + cost[u][v];
                parent[v] = u;

                if(!inQ[v]){
                    inQ[v] = true;
                    Q.push(v);
                }
            }
        }
    }

    return (d[sink] != INF);
}

void MCMF(void) {
    int answer = 0;
    while(1) {
        if(!SPFA())
            break;
        int min_flow = INF;
        int u = sink;
        while(1) {
            if(u == source)
                break;
            int prev = parent[u];
            min_flow = min(min_flow, capacity[prev][u] - flow[prev][u]);
            u = prev;
        }
        u = sink;
        while(1) {
            if(u == source)
                break;
            int prev = parent[u];
            answer += min_flow * cost[prev][u];
            flow[prev][u] += min_flow;
            flow[u][prev] -= min_flow;
            u = prev;
        }
    }

    printf("%d\n", -answer);
}

int main(void) {
    while(1) {
        if(input())
            break;
        MCMF();
    }
    return 0;
}
