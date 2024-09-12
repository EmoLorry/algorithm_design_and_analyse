#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <float.h>

struct Point {
    int x, y;
};

// 按x坐标比较点的函数
bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

// 按y坐标比较点的函数
bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

double distance(const Point& p1, const Point& p2) {
    double dx = static_cast<double>(p1.x) - static_cast<double>(p2.x);
    double dy = static_cast<double>(p1.y) - static_cast<double>(p2.y);
    return sqrt(dx * dx + dy * dy);
}

// 暴力方法返回P[]中两点之间的最小距离
double bruteForce(const std::vector<Point>& P, int n) {
    double min_dist = FLT_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            double d = distance(P[i], P[j]);
            if (d < min_dist) {
                min_dist = d;
            }
        }
    }
    return min_dist;
}

// 辅助函数，找到大小为size的strip[]中最近点的距离，strip[]中的所有点按y坐标排序
double stripClosest(const std::vector<Point>& strip, int size, double d) {
    double min_dist = d;
    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min_dist; ++j) {
            double dist = distance(strip[i], strip[j]);
            if (dist < min_dist) {
                min_dist = dist;
            }
        }
    }
    return min_dist;
}

// 递归函数找到最小距离，数组P包含所有按x坐标排序的点
double closestUtil(std::vector<Point>& Px, std::vector<Point>& Py, int n) {
    if (n <= 3) return bruteForce(Px, n);

    int mid = n / 2;
    Point midPoint = Px[mid];

    std::vector<Point> Pyl, Pyr;
    for (int i = 0; i < n; ++i) {
        if (Py[i].x <= midPoint.x) {
            Pyl.push_back(Py[i]);
        } else {
            Pyr.push_back(Py[i]);
        }
    }

    std::vector<Point> Pl(Px.begin(), Px.begin() + mid);
    std::vector<Point> Pr(Px.begin() + mid, Px.end());

    double dl = closestUtil(Pl, Pyl, mid);
    double dr = closestUtil(Pr, Pyr, n - mid);

    double d = std::min(dl, dr);

    std::vector<Point> strip;
    for (int i = 0; i < n; ++i) {
        if (abs(Py[i].x - midPoint.x) < d) {
            strip.push_back(Py[i]);
        }
    }

    return std::min(d, stripClosest(strip, strip.size(), d));
}

// 主函数找到最小距离，这个方法主要使用closestUtil()
double closest(std::vector<Point>& P, int n) {
    std::vector<Point> Px = P;
    std::vector<Point> Py = P;
    std::sort(Px.begin(), Px.end(), compareX);
    std::sort(Py.begin(), Py.end(), compareY);

    return closestUtil(Px, Py, n);
}

int main() {
    int n(0);
    while (scanf("%d", &n) != EOF) {
        std::vector<Point> P(n);
        for (int i = 0; i < n; ++i) {
            scanf("%d %d", &P[i].x, &P[i].y);
        }
        double result = closest(P, n);
        printf("%.4f\n", result);
    }

    return 0;
}

