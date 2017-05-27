#include <iostream>
#include <list>
#include <queue>

#define INF 99999

using namespace std;

int V, E;
vector<list<pair<int, int>>> G;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
vector<int> dist, nearest;

void dijkstra() {

    dist.assign(V + 1, INF);
    nearest.assign(V + 1, 0);
    pq.push(make_pair(0, 1));
    dist[1] = 0;


    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for(list<pair<int, int>>::iterator it = G[u].begin(); it != G[u].end(); it++) {
            int v = it->first;
            int w = it->second;

            if(dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                nearest[v] = u;
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

int main(void) {
    cin >> V >> E;

    G.resize(V + 1);

    for(int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back(make_pair(v, w));
    }
    dijkstra();

    cout << "distance : ";
    for(int i = 1; i <= V; i++)
        cout << dist[i] << " ";
    cout << endl;

    cout << "nearest : ";
    for(int i = 1; i <= V; i++)
        cout <<  nearest[i] << " ";
    cout <<  " ";


    return 0;
}
