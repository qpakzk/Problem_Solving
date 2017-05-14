/*
 * Problem Solving Assignment7-1 : DSLR
 * https://www.acmicpc.net/problem/9019
 */


#include <cstdio>
#include <cstring>
#include <queue>
#include <stack>
#define MAXLEN 10000
using namespace std;

int before[MAXLEN];
bool visited[MAXLEN];
char op[MAXLEN];

int D(int n) {
    n *= 2;
    n %= 10000;
    return n;
}

int S(int n) {
    if(n == 0)
        n = 9999;
    else
        n -= 1;

    return n;
}

int L(int n) {
    int h = n / 1000;
    n %= 1000;
    n *= 10;
    n += h;

    return n;
}

int R(int n) {
    int h = n % 10;
    n /= 10;
    n += h * 1000;

    return n;
}

int main(void) {
    int T;
    int start, end, cal, tmp;
    queue<int> q;
    stack<int> s;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &start, &end);

        memset(before, 0, sizeof(before));
        memset(visited, 0, sizeof(visited));
        memset(op, 0, sizeof(op));
        q.push(start);
        visited[start] = true;
        while(!q.empty()) {
            cal = q.front();
            q.pop();

            if(cal == end) {
                while(!q.empty())
                    q.pop();
                break;
            }

            tmp = cal;
            tmp = D(tmp);
            if(!visited[tmp]) {
                before[tmp] = cal;
                op[tmp] = 'D';
                q.push(tmp);
                visited[tmp] = true;
            }

            tmp = cal;
            tmp = S(tmp);
            if(!visited[tmp]) {
                before[tmp] = cal;
                op[tmp] = 'S';
                q.push(tmp);
                visited[tmp] = true;
            }

            tmp = cal;
            tmp = L(tmp);
            if(!visited[tmp]) {
                before[tmp] = cal;
                op[tmp] = 'L';
                q.push(tmp);
                visited[tmp] = true;
            }

            tmp = cal;
            tmp = R(tmp);
            if(!visited[tmp]) {
                before[tmp] = cal;
                op[tmp] = 'R';
                q.push(tmp);
                visited[tmp] = true;
            }
        }

        tmp = end;
        while(1) {
            s.push(tmp);
            if(tmp == start)
                break;
            tmp = before[tmp];
        }

        s.pop();
        while(!s.empty()) {
            printf("%c", op[s.top()]);
            s.pop();
        }
        printf("\n");
    }

    return 0;
}
