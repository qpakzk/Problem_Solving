/*
 * Problem Solving Assignment8-1 : 우주신과의 교감
 * https://www.acmicpc.net/problem/1774
 */

#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
using namespace std;

#define MAXLEN 1001

struct Coordinate {
    int num;
    int x, y;
} coord[MAXLEN];

struct node {
    int parent;
    int depth;
} tree[MAXLEN];

struct Edge {
    int n1, n2;
    double w;
};

void makeset(int i) {
    tree[i].parent = i;
    tree[i].depth = 0;
}

void init(int n) {
    for(int i = 1; i <= n; i++)
        makeset(i);
}

void merge(int p, int q)  {
    if(tree[p].depth == tree[q].depth) {
        tree[p].depth += 1;
        tree[p].parent = q;
    }
    else if(tree[p].depth < tree[q].depth)
        tree[p].parent = q;
    else
        tree[q].parent = p;
}

bool equal(int p, int q) {
    if(p == q)
        return true;
    else
        return false;
}

int find(int i) {
    int j = i;
    while(tree[j].parent != j)
        j = tree[j].parent;
    return j;
}

vector<Edge> included_edge;
bool is_inclued(int n1, int n2) {
    bool included = false;
    for(int i = 0; i < included_edge.size(); i++)
        if(included_edge[i].n1 == n1 && included_edge[i].n2 == n2) {
            included = true;
            break;
        }

    return included;
}

double distance(int n1, int n2) {
    double x_len = coord[n1].x - coord[n2].x;
    double y_len = coord[n1].y - coord[n2].y;
    double dist = sqrt(x_len * x_len + y_len * y_len);

    return dist;
}
vector<Edge> edge_set;
queue<Edge> Q;

bool comp(Edge e1, Edge e2) {
    if(e1.w == e2.w) {
        if (e1.n1 == e2.n1)
            return e1.n2 < e2.n2;
        return e1.n1 < e2.n1;
    }

    return e1.w < e2.w;
}

double result;
void kruskal(int n) {
    int count = 1;
    while(count <= n - 1 && !Q.empty()) {
        Edge e = Q.front();
        Q.pop();
        int p = find(e.n1);
        int q = find(e.n2);
        if(!equal(p, q)) {
            merge(p, q);
            result += e.w;
            count++;
        }
    }
}

int main(void) {
    int N, M;
    scanf("%d %d", &N, &M);
    for(int n = 1; n <= N; n++) {
        coord[n].num = n;
        scanf("%d %d", &coord[n].x, &coord[n].y);
    }

    for(int m = 1; m <= M; m++) {
        int n1, n2;
        Edge e;
        scanf("%d %d", &n1, &n2);
        if(n1 < n2) {
            e.n1 = n1;
            e.n2 = n2;
        }
        else {
            e.n1 = n2;
            e.n2 = n1;
        }

        included_edge.push_back(e);
    }

    for(int i = 1; i <= N - 1; i++)
        for(int j = i + 1; j <= N; j++) {
            if(!is_inclued(i, j)) {
                Edge e;
                e.n1 = i;
                e.n2 = j;
                e.w = distance(i, j);
                edge_set.push_back(e);
            }
        }

    sort(edge_set.begin(), edge_set.end(), comp);

    for(int i = 0; i < edge_set.size(); i++)
        Q.push(edge_set[i]);

    init(N);
    for(int i = 0; i < included_edge.size(); i++) {
        int p = find(included_edge[i].n1);
        int q = find(included_edge[i].n2);
        if(!equal(p, q))
            merge(p, q);
    }

    int node_count = 0;
    for(int i = 1; i <= N; i++)
        if(tree[i].parent == i)
            node_count++;

    result = 0.0;
    kruskal(node_count);
    printf("%.2lf\n", result);
    return 0;
}