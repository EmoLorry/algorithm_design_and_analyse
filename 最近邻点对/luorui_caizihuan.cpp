#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <float.h>

struct Point {
    int x, y;
};
// 按y坐标比较点的函数
bool compareY(Point a, Point b) {
    return a.y <= b.y;
}
bool compareX(Point a, Point b) {
    return a.x <= b.x;
}


double distance(Point p1, Point p2) {
    double dx = double(p1.x) - double(p2.x);
    double dy = double(p1.y) - double(p2.y);
    return dx * dx + dy * dy;
}

double bruteForce(std::vector<Point>& P, int start, int end) {
    double min_dist = DBL_MAX;
    for (int i = start; i < end; ++i) {
        for (int j = i + 1; j < end; ++j) {
            if (distance(P[i], P[j]) < min_dist) {
                min_dist = distance(P[i], P[j]);
            }
        }
    }
    return min_dist;
}

double stripClosest(std::vector<Point>& strip, int size, double d) {
    double min_dist = d;
    std::sort(strip.begin(), strip.begin() + size, compareY);
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (double(strip[j].y - strip[i].y)*double(strip[j].y - strip[i].y)) < min_dist; ++j) {
            if (distance(strip[i], strip[j]) < min_dist) {
                min_dist = distance(strip[i], strip[j]);
            }
        }
    }
    return min_dist;
}

double closestUtil(std::vector<Point>& P, int start, int end) {
    if (end - start <= 3) return bruteForce(P, start, end);

    int mid = (start + end) >>1;
    Point midPoint = P[mid];

    double dl = closestUtil(P, start, mid+1);
    double dr = closestUtil(P, mid+1, end);

    double d = std::min(dl, dr);

    std::vector<Point> strip;
    for (int i = start; i < end; ++i) {
        if ((double(P[i].x - midPoint.x)*double(P[i].x - midPoint.x))<= d) {
            strip.push_back(P[i]);
        }
    }

    return std::min(d, stripClosest(strip, strip.size(), d));
}

double closest(std::vector<Point>& P, int n) {
    std::sort(P.begin(), P.end(), compareX);
    return closestUtil(P, 0, n);
}

int main() {
    int n(0);
    while(scanf("%d", &n) != EOF)
    {
        std::vector<Point> P(n);
        for(int i=n-1;i>=0; --i){
            scanf("%d %d", &P[i].x, &P[i].y);
        }
        double result0 = closest(P, n);
        double result = sqrt(result0);
		printf("%.4f\n",result);
    }

    return 0;
}

