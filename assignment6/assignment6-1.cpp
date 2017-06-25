/*
 * Problem Solving Assignment6-1 : Cows
 * https://www.acmicpc.net/problem/6850
 */

#include <cstdio>
#include <algorithm>
#include <cmath>
#include <stack>
using namespace std;

#define MAXLEN 10001
#define PI 3.141592

struct Point {
    int x;
    int y;
} point[MAXLEN], pivot;

bool comp1(Point A, Point B) {
    if(A.y == B.y)
        return A.x < B.y;
    else
        return A.y < B.y;
}

bool comp2(Point A, Point B) {
    double radian_A = atan2(A.y - pivot.y, A.x - pivot.x);
    double radian_B = atan2(B.y - pivot.y, B.x - pivot.x);
    if(radian_A < 0)
        radian_A += 2 * PI;
    if(radian_B < 0)
        radian_B += 2 * PI;

    if(radian_A < radian_B)
        return 1;
    else
        return 0;
}

int direction(Point A, Point B, Point C) {
    int result = (A.x * B.y + B.x * C.y + C.x * A.y) - (A.x * C.y + B.x * A.y + C.x * B.y);
    return result;
}

double sign_area(Point A, Point B, Point C) {
    double area = (double) direction(A, B, C);
    return area / 2.0;

}

int main(void) {
    int N;
    scanf("%d", &N);
    for(int n = 0; n < N; n++)
        scanf("%d %d", &point[n].x, &point[n].y);
    sort(point, point + N, comp1);
    pivot = point[0];

    sort(point + 1, point + N, comp2);

    stack<Point> s1;
    s1.push(point[0]);
    s1.push(point[1]);

    int top = 2;
    while(top < N) {
        while(s1.size() >= 2) {
            Point p1, p2;
            p1 = s1.top();
            s1.pop();
            p2 = s1.top();
            if (direction(p2, p1, point[top]) > 0) {
                s1.push(p1);
                break;
            }
        }
        s1.push(point[top]);
        top++;
    }

    stack<Point> s2;
    while(!s1.empty()) {
        Point pt = s1.top();
        s2.push(pt);
        s1.pop();
    }

    Point piv = s2.top();
    s2.pop();
    Point pt1 = s2.top();
    s2.pop();
    Point pt2;
    double area = 0.0;
    while(!s2.empty()) {
        pt2 = s2.top();
        s2.pop();
        area += sign_area(piv, pt1, pt2);
        pt1 = pt2;
    }
    printf("%d\n", (int) area / 50);
    return 0;
}