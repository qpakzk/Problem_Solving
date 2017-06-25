/*
 * Problem Solving Assignment10 : 열혈강호 4
 * https://www.acmicpc.net/problem/11378
 */
#include <cstdio>
#include <cstring>
#include <vector>

#define MAXLEN 2001
using namespace std;

int N, M, K;
vector<int> adj[MAXLEN];
int visited[MAXLEN];
int parent[MAXLEN];
bool dfs(int u) {
    if(!visited[u]) {
        visited[u] = true;
        for(int v : adj[u])
            if (parent[v] == 0 || dfs(parent[v])) {
                parent[v] = u;
                return true;
            }
    }
    return false;
}

int main(void) {
    scanf("%d %d %d", &N, &M, &K);
    for(int n = 1; n <= N; n++) {
        int x;
        scanf("%d", &x);
        for(int i = 1; i <= x; i++) {
            int y;
            scanf("%d", &y);
            adj[n].push_back(y);
        }
    }

    int result = 0;
    for(int i = 1; i <= N; i++) {
        memset(visited, 0, sizeof(visited));
        if(dfs(i))
            result++;
    }

    for(int i = 1; i <= N; i++) {
        memset(visited, 0, sizeof(visited));
        if(K > 0 && dfs(i)) {
            K--;
            result++;
            i--;
            continue;
        }
    }
    printf("%d\n", result);
    return 0;
}
