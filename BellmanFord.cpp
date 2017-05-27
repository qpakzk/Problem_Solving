#include <iostream>
#include <vector>
#define INF INT_MAX

using namespace std;

struct Edge {
    int u, v, w;
};

int NODES, EDGES;
vector<Edge> edges;
vector<int> dist;
vector<int> previous;

int main(void) {
    int i, j;

    cin >> NODES >> EDGES;
    dist.resize(NODES);
    previous.resize(NODES);

    for(i = 0; i < NODES; ++i) {
        dist[i] = INF;
        previous[i] = 0;
    }

    dist[0] = 0;

    edges.resize(EDGES);
    for(int e = 0; e < EDGES; ++e)
        cin >> edges[e].u >> edges[e].v >> edges[e].w;

    for(i = 0; i < NODES - 1; ++i) {
        for (j = 0; j < EDGES; ++j) {
            if (dist[edges[j].u] + edges[j].w < dist[edges[j].v]) {
                dist[edges[j].v] = dist[edges[j].u] + edges[j].w;
                previous[edges[j].v] = edges[j].u;
            }
        }
    }
    cout << "distance : ";
    for(int i = 0; i < NODES; i++)
        cout << dist[i] << " ";
    cout << endl;

    cout << "previous : ";
    for(int i = 0; i < NODES; i++)
        cout << previous[i] << " ";
    cout << endl;

    for(j = 0; j < EDGES; ++j) {
        if(dist[edges[j].u] + edges[j].w < dist[edges[j].v]) {
            printf("Graph contanis a negative-weight cycle!!\n");
            exit(1);
        }
     }

    return 0;
}
