/*
 * Problem Solving Assignment11-2 : 순열장난
 * https://www.acmicpc.net/problem/10597
 */

#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

char input[92];
int max_num, size;
vector<int> result;
bool visited[51];
bool end_flag;

void dfs(int idx) {
    if(end_flag)
        return;

    if (idx == size) {
        end_flag = true;
        for (int i = 0; i < result.size(); i++)
            printf("%d ", result[i]);
    }

    int num;
    if (idx + 1 < size) {
        num = (input[idx] - '0') * 10 + (input[idx + 1] - '0');
        if (num >= 1 && num <= max_num)
            if(!visited[num]) {
                visited[num] = true;
                result.push_back(num);
                dfs(idx + 2);
                visited[num] = false;
                result.pop_back();
            }
    }

    if (idx < size) {
        num = input[idx] - '0';
        if (num >= 1 && num <= max_num)
            if(!visited[num]) {
                visited[num] = true;
                result.push_back(num);
                dfs(idx + 1);
                visited[num] = false;
                result.pop_back();
            }
    }
}

int main(void) {
    scanf("%s", input);
    size = (int) strlen(input);
    if(size < 10)
        max_num = size;
    else
        max_num = 9 + (size - 9) / 2;
    dfs(0);
    return 0;
}