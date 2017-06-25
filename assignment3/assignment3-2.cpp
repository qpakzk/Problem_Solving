/*
 * 문제해결 3주차 과제3-2 : 알 수 없는 문장
 * https://www.acmicpc.net/problem/1099
 */

#include <iostream>
#include <algorithm>
#define MAXLEN 51
#define INF 1000000
using namespace std;

string word[MAXLEN];
int dp[MAXLEN];

bool is_same_sen(string str1, string str2) {
    sort(str1.begin(), str1.end());
    sort(str2.begin(), str2.end());

    if(str1 == str2)
        return true;
    else
        return false;
}

int cost(string str1, string str2) {
    int count = 0;
    for(int i = 0; i < str1.size(); i++)
        if(str1[i] != str2[i])
            count++;

    return count;
}
int main(void) {
    string sentence;
    cin >> sentence;

    int N;
    scanf("%d", &N);

    for(int i = 1; i <= N; i++)
        cin >> word[i];

    int senlen = (int) sentence.size();
    for(int i = 1; i <= senlen; i++)
        dp[i] = INF;

    for(int i = 1; i <= senlen; i++) {
        for(int j = 1; j <= N; j++) {
            if(word[j].size() <= i) {
                if(is_same_sen(word[j], sentence.substr((unsigned long) i - word[j].size(), word[j].size()))) {
                    if(dp[i] == INF) {
                        if(dp[i - word[j].size()] != INF)
                            dp[i] = dp[i - word[j].size()] + cost(word[j], sentence.substr((unsigned long) i - word[j].size(), word[j].size()));
                    }
                    else {
                        dp[i] = min(dp[i], dp[i - word[j].size()] + cost(word[j], sentence.substr((unsigned long) i - word[j].size(), word[j].size())));
                    }
                }
            }
        }
    }
    if(dp[senlen] == INF)
        printf("-1\n");
    else
        printf("%d\n", dp[senlen]);
    return 0;
}