/*
 * Problem Solving Assignment9-2 : 도로포장
 * https://www.acmicpc.net/problem/1162
 */

#include <cstdio>
#include <vector>
#include <list>
#include <queue>
#include <climits>
#define INF INT_MAX

using namespace std;

int N, M, K;
vector<list<pair<int, int>>> G;
priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<pair<pair<int, int>, int>>> pq;
vector<vector<int>> dp;

void dijkstra() {
    dp.resize(K + 1);
    for(int i = 0; i <= K; i++)
        dp[i].assign(N + 1, INF);

    pq.push(make_pair(make_pair(0, 1), 0));
    dp[0][1] = 0;

    while(!pq.empty()) {
        int w1 = pq.top().first.first;
        int v1 = pq.top().first.second;
        int k = pq.top().second;
        pq.pop();

        for(list<pair<int, int>>::iterator it = G[v1].begin(); it != G[v1].end(); it++) {
            int v2 = it->first;
            int w2 = it->second;

            if(dp[k][v1] + w2 < dp[k][v2]) {
                dp[k][v2] = dp[k][v1] + w2;
                pq.push(make_pair(make_pair(dp[k][v2], v2), k));
            }
        }

        for(list<pair<int, int>>::iterator it = G[v1].begin(); it != G[v1].end(); it++) {
            int v2 = it->first;
            if(k + 1 <= K)
                if(w1 < dp[k + 1][v2]) {
                    dp[k + 1][v2] = w1;
                    pq.push(make_pair(make_pair(dp[k + 1][v2], v2), k + 1));
                }
        }
    }
}

int main(void) {
    scanf("%d %d %d", &N, &M, &K);

    G.resize(N + 1);
    for(int i = 0; i < M; i++) {
        int v1, v2, w;
        scanf("%d %d %d", &v1, &v2, &w);
        G[v1].push_back(make_pair(v2, w));
        G[v2].push_back(make_pair(v1, w));
    }

    dijkstra();

    int m = dp[0][N];
    for(int i = 1; i <= K; i++)
        if(dp[i][N] < m)
            m = dp[i][N];

    printf("%d\n", m);
    return 0;
}
