/*
 * 문제해결 1주차 과제 1-2 : 오일러 회로
 * https://www.acmicpc.net/problem/1199
 */

#include <iostream>
#include <cstdio>
#include <queue>
#include <ctime>

int N;
int matrix[2000][2000];
int degree[2000];
int start;
std::queue<int> path;

void euler(int node, int num) {
	for(int i = 1; i <= N; i++) { 
		if(matrix[node][i] > 0) {
			if(degree[start] == 1 && i == start && num != 1)
				continue;
			path.push(i);
			matrix[node][i]--;
			matrix[i][node]--;
			degree[i]--;
			degree[node]--;
			num--;
			euler(i, num);
		}
	}
}

int main(void) {
	scanf("%d", &N);
		
	for(int i = 1; i <= N; i++) 
		for(int j = 1; j <= N; j++)
			scanf("%d", &matrix[i][j]);
	
	int sum = 0;
	bool isLinked = true;
	for(int i = 1; i <= N && isLinked; i++) {
		for(int j = 1; j <= N; j++)
			degree[i] += matrix[i][j];
		if(degree[i] % 2 == 1 || degree[i] == 0) {
			isLinked = false;
			break;
		}
		
		sum += degree[i];
	}	
	
	if(N == 1 &&  matrix[1][1] == 0)
		printf("%d\n", 1);
	else if(isLinked) {
		int num_edge = sum / 2;		
		srand((unsigned)time(NULL));
		start = rand() % N + 1;
		path.push(start);
		euler(start, num_edge);

		while(!path.empty()) {
			printf("%d ", path.front());
			path.pop();
		}
		printf("\n");
	}	
	else 
		printf("%d\n", -1);

	return 0;
}
