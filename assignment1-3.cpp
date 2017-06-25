/*
 * 문제해결 1주차 과제 1-3 : 이분 그래프
 * https://www.acmicpc.net/problem/1707
 */

#include <iostream>
#include <vector>
#include <queue>
using namespace std;


int main(void) {
	int K;
	cin >> K;
	for(int test = 1; test <= K; test++) {
		int V, E;
		cin >> V >> E;

		int edge[2];
		vector<int> graph[20001];
		for(int i = 1; i <= E; i++) {
			cin >> edge[0] >> edge[1];
      		graph[edge[0]].push_back(edge[1]);
      		graph[edge[1]].push_back(edge[0]);
   		}

		/*
		for(int i = 1; i <= V; i++) { 
			cout << "size: " << graph[i].size() << endl;
			cout << i << ": ";
			for(int j = 0; j < graph[i].size(); j++)
				cout << graph[i][j] << " ";
			cout << endl << endl;
		}
		*/

		vector<int> vertex;
		vertex.assign(V + 1, 0);
		
		queue<int> next_visit;
		bool isBipartiteGraph = true;
		for(int i = 1; i <= V && isBipartiteGraph; i++) {
			if(vertex[i] == 0) {
				vertex[i] = 1;
				next_visit.push(i);	
			}

			while(!next_visit.empty() && isBipartiteGraph) {
				int v = next_visit.front();
				next_visit.pop();
				//cout << "test: v = " << v << endl;
				for(int j = 0; j < graph[v].size(); j++) {	
					int adjust = graph[v][j];
					
					//cout << "test: adj = " << adjust << endl;
					if(vertex[adjust] == 0) {
						if(vertex[v] == 1)
							vertex[adjust] = 2;
						else
							vertex[adjust] = 1;
						
						//cout << "test: vertex[" << adjust << "] = " << vertex[adjust] << endl;

						next_visit.push(adjust);
					}
					else if(vertex[v] == vertex[adjust]) {
						//cout << "enter" << endl;
						isBipartiteGraph = false;
						break;
					}
				}
			}
		}
		
		/*
		cout << "vertex >> " << endl;
		for(int i = 1; i <= V; i++)
			cout << i << ": " << vertex[i] << endl;
		*/
		if(isBipartiteGraph)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
