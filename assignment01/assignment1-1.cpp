/*
 * 문제해결 1주차 과제1-1: 명령프롬프트
 * https://www.acmicpc.net/problem/1032
 */
#include <cstdio>
#include <cstring>

int main(void) {
	int N, i, j, len, word, isSame;
	char file[100][100], result[100];

	scanf("%d", &N);
	for(i = 0; i < N; i++)
		scanf("%s", file[i]);
	len = strlen(file[0]);
	
	for(i = 0; i < len; i++) {	
		word = file[0][i];
		isSame = 1;		
		for(j = 1; j < N; j++)
			if(word != file[j][i]) {
				result[i] = '?';
				isSame = 0;
				break;
			}	
		if(isSame == 1)
			result[i] = word;
	}
	result[len] = '\0';

	printf("%s\n", result);
	return 0;
}
