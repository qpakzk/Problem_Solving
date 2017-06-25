/*
 * Problem Solving Assignment9-1 : 오민식의 고민
 * https://www.acmicpc.net/problem/1219
 */

#include <cstdio>
#include <vector>
#include <climits>

#define INF INT_MAX

using namespace std;

int N, S, D, M;
bool is_included;
vector<pair<pair<int, int>, long long>> edges;
vector<long long> dist;
vector<int> earn;
vector<vector<bool>> link;

void bellman_ford() {
    dist.resize(N);
    for(int i = 0; i < N; i++)
        dist[i] = -INF;
    dist[S] = earn[S];

    for(int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            int v1 = edges[j].first.first;
            int v2 = edges[j].first.second;
            long long w = earn[v2] - edges[j].second;

            if (dist[v1] != -INF && dist[v1] + w > dist[v2])
                dist[v2] = dist[v1] + w;
        }
    }

    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            for(int k = 0; k < N; k++) {
                if (link[j][i] && link[i][k])
                    link[j][k] = true;
            }
        }
    }

    is_included = false;
    for (int j = 0; j < M; j++) {
        int v1 = edges[j].first.first;
        int v2 = edges[j].first.second;
        long long w = earn[v2] - edges[j].second;

        if (dist[v1] + w > dist[v2]) {
            if(link[S][v1] && link[S][v2] && link[v1][D] && link[v2][D]) {
                is_included = true;
                break;
            }
        }
    }
}

int main(void) {
    scanf("%d %d %d %d", &N, &S, &D, &M);

    link.resize(N);
    for(int i = 0; i < N; i++)
        link[i].assign(N, false);

    edges.resize(M);
    for(int m = 0; m < M; m++) {
        int v1, v2, w;
        scanf("%d %d %d", &v1, &v2, &w);
        link[v1][v2] = true;

        edges[m].first.first = v1;
        edges[m].first.second = v2;
        edges[m].second = w;
    }

    earn.resize(N);
    for(int i = 0; i < N; i++) {
        int e;
        scanf("%d", &e);
        earn[i] = e;
    }

    bellman_ford();

    if(is_included)
        printf("Gee\n");
    else if(dist[D] == -INF)
        printf("gg\n");
    else
        printf("%lld\n", dist[D]);

    return 0;
}
