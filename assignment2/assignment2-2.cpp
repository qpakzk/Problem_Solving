/*
 * 문제해결 2주차 과제2-2: 트리의 높이와 너비
 * https://www.acmicpc.net/problem/2250
 */

#include <cstdio>
#include <cstring>

#define MAX_NODES 10001

int N;
int root;
int max_level;
int visited[MAX_NODES];
int vertical[MAX_NODES];//값 : 노드의 번호, 인덱스 : 위치
int location;
int horizontal[MAX_NODES];//값 : 레벨, 인덱스 : 노드의 번호

void DFS(int node, int tree[][2], int level) {
    if(node == -1)
        return;

    DFS(tree[node][0], tree, level + 1);
    if(tree[node][0] == -1 || (visited[tree[node][0]] == 1 && visited[node] == 0)) {
        vertical[location] = node;
        if(max_level < level)
            max_level = level;
        horizontal[node] = level;
        visited[node] = 1;
        location++;
    }
    DFS(tree[node][1], tree, level + 1);
}

int main(void) {
    scanf("%d", &N);

    int node[N + 1][3];
    for(int i = 1; i <= N; i++)
        scanf("%d %d %d", &node[i][0], &node[i][1], &node[i][2]);

    int tree[N + 1][2];

    for(int i = 1; i <= N; i++) {
        tree[node[i][0]][0] = node[i][1];
        tree[node[i][0]][1] = node[i][2];
    }

    int nodes[N + 1];
    memset(nodes, 0, sizeof(nodes));

    for(int  i = 1; i <= N; i++) {
        if(tree[i][0] != -1)
            nodes[tree[i][0]]++;
        if(tree[i][1] != -1)
            nodes[tree[i][1]]++;
    }

    for(int i = 1; i <= N; i++)
        if(nodes[i] == 0) {
            root = i;
            break;
        }

    int level = 1;
    location = 1;
    DFS(root, tree, level);

    int matrix[max_level + 1][N + 1];
    memset(matrix, 0, sizeof(matrix));

    for(int i = 1; i <= N; i++)
        matrix[horizontal[vertical[i]]][i] = vertical[i];

    /*
    printf("vertical>>\n");
    for(int i = 1; i <= N; i++)
        printf("%d - %d\n", i, vertical[i]);

    printf("horizontal>>\n");
    for(int i = 1; i <= N; i++)
        printf("%d - %d\n", i, horizontal[i]);
    printf("max_level : %d\n", max_level);

    for(int i = 1; i <= max_level; i++) {
        for(int j = 1; j <= N; j++) {
            printf("%2d  ", matrix[i][j]);
        }
        printf("\n");
    }
    */

    int max_width = 0;
    int min_level = N + 1;
    for(int i = max_level; i >= 1; i--) {
        int left;
        int right;
        int width;
        for(int j = 1; j <= N; j++)
            if(matrix[i][j] != 0) {
                left = j;
                break;
            }

        for(int j = N; j >= 1; j--)
            if(matrix[i][j] != 0) {
                right = j;
                break;
            }
        width = right - left + 1;
        if(max_width <= width) {
            max_width = width;
            min_level = i;
        }
    }

    printf("%d %d\n", min_level, max_width);
    return 0;
}