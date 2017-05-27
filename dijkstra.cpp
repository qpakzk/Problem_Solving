#include <iostream>
#include <vector>

#define INF 99999
using namespace std;

int V, E;
vector<int> nearest, length;
vector<vector<int> > W;

void dijkstra() {
    int vnear;

    nearest.resize(V + 1);
    length.resize(V + 1);

    for(int i = 2; i <= V; i++) {
        nearest[i] = 1;
        length[i] = W[1][i];
    }

    int len = 1;
    while(len <= V - 1) {
        int min = INF;
        for(int i = 2; i <= V; i++) {
            if(0 <= length[i] && length[i] <= min) {
                min = length[i];
                vnear = i;
            }
        }

        for(int i = 2; i <= V; i++) {
            if(length[vnear] + W[vnear][i] < length[i]) {
                length[i] = length[vnear] + W[vnear][i];
                nearest[i] = vnear;
            }
        }

        length[vnear] = -1;
        len++;
    }

}

int main(void) {
    cin >> V >> E;

    W.resize(V + 1);
    for(int i = 0; i <= V; i++)
        W[i].assign(V + 1, INF);

    for(int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        W[u][v] = w;
    }
    dijkstra();

    for(int i = 1; i <= V; i++)
        cout <<  nearest[i] << " ";
    cout << endl;
    return 0;
}
