#include <vector>
#include <cmath>
#include <algorithm>

struct Point {
    int x, y;
};

// ��x����Ƚϵ�ĺ���
bool compareX(Point a, Point b) {
    return a.x < b.x;
}

// ��y����Ƚϵ�ĺ���
bool compareY(Point a, Point b) {
    return a.y < b.y;
}

double distance(Point p1, Point p2) {
    double dx = static_cast<double>(p1.x) - static_cast<double>(p2.x);
    double dy = static_cast<double>(p1.y) - static_cast<double>(p2.y);
    return sqrt(dx * dx + dy * dy);
}

// ������������P[]������֮�����С����
double bruteForce(std::vector<Point>& P, int n) {
    double min_dist = FLT_MAX;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (distance(P[i], P[j]) < min_dist) {
                min_dist = distance(P[i], P[j]);
            }
        }
    }
    return min_dist;
}

// �����������ҵ���СΪsize��strip[]�������ľ��룬strip[]�е����е㰴y��������
double stripClosest(std::vector<Point>& strip, int size, double d) {
    double min_dist = d;
    std::sort(strip.begin(), strip.begin() + size, compareY);

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min_dist; ++j) {
            if (distance(strip[i], strip[j]) < min_dist) {
                min_dist = distance(strip[i], strip[j]);
            }
        }
    }
    return min_dist;
}

// �ݹ麯���ҵ���С���룬����P�������а�x��������ĵ�
double closestUtil(std::vector<Point>& P, int n) {
    if (n <= 3) return bruteForce(P, n);

    int mid = n / 2;
    Point midPoint = P[mid];

    std::vector<Point> Pl(P.begin(), P.begin() + mid);
    std::vector<Point> Pr(P.begin() + mid, P.end());

    double dl = closestUtil(Pl, mid);
    double dr = closestUtil(Pr, n - mid);

    double d = std::min(dl, dr);

    std::vector<Point> strip;
    for (int i = 0; i < n; ++i) {
        if (abs(P[i].x - midPoint.x) < d) {
            strip.push_back(P[i]);
        }
    }

    return std::min(d, stripClosest(strip, strip.size(), d));
}

// �������ҵ���С���룬���������Ҫʹ��closestUtil()
double closest(std::vector<Point>& P, int n) {
    std::sort(P.begin(), P.end(), compareX);
    return closestUtil(P, n);
}

int main() {
    int n(0);
    while(scanf("%d", &n) != EOF)
    {
        std::vector<Point> P(n);
        for(int i=n-1;i>=0; --i){
            scanf("%d %d", &P[i].x, &P[i].y);

        }
        double result = closest(P, n);
        printf("%.4f\n",result);
    }

    return 0;
}
