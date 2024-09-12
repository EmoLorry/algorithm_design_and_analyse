#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <float.h>

struct Point {
    int x, y;
};

bool compareX(Point a, Point b) {
    return a.x < b.x;
}

bool compareY(Point a, Point b) {
    return a.y < b.y;
}

double distance(Point p1, Point p2) {
    double dx = static_cast<double>(p1.x) - static_cast<double>(p2.x);
    double dy = static_cast<double>(p1.y) - static_cast<double>(p2.y);
    return dx * dx + dy * dy;
}

double bruteForce(std::vector<Point>& P, int start, int end) {
    double min_dist = FLT_MAX;
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

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y)*(strip[j].y - strip[i].y) < min_dist; ++j) {
            if (distance(strip[i], strip[j]) < min_dist) {
                min_dist = distance(strip[i], strip[j]);
            }
        }
    }
    return min_dist;
}

double closestUtil(std::vector<Point>& P, int start, int end) {
    if (end - start <= 3) return bruteForce(P, start, end);

    int mid = (start + end) / 2;
    Point midPoint = P[mid];

    double dl = closestUtil(P, start, mid);
    double dr = closestUtil(P, mid, end);

    double d = std::min(dl, dr);

    std::vector<Point> strip;
    for (int i = start; i < end; ++i) {
        if ((P[i].x - midPoint.x)*(P[i].x - midPoint.x)<= d) {
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

