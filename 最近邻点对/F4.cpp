#include <algorithm>
#include <cmath>
#include <fstream>

using namespace std;

const int MAX_N = 1000000;
struct Point {
    double x, y;
} p[MAX_N];

int n, temp[MAX_N];

bool cmp(const Point& A, const Point& B) {
    if (A.x == B.x)
        return A.y < B.y;
    else
        return A.x < B.x;
}

bool cmds(const int& a, const int& b) {
    return p[a].y < p[b].y;
}

double distance(int i, int j) {
    return sqrt((p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y));
}

double merge(int left, int right) {
    double dis = 1e20; // 初始化距离
    if (left == right) // 递归出口
        return dis;

    if (left + 1 == right)
        return distance(left, right);

    int mid = (left + right) / 2;
    double d1 = merge(left, mid);
    double d2 = merge(mid + 1, right);
    dis = min(d1, d2);

    int k = 0;
    // 把有可能更近的点记录下来
    for (int i = left; i <= right; ++i) {
        if (fabs(p[i].x - p[mid].x) <= dis)
            temp[k++] = i;
    }

    // 根据y坐标排序
    sort(temp, temp + k, [&](int a, int b) { return cmds(a, b); });

    for (int i = 0; i < k; ++i) // 枚举找到最小距离
        for (int j = i + 1; j < k && p[temp[j]].y - p[temp[i]].y < dis; ++j)
            dis = min(dis, distance(temp[i], temp[j])); // 第三种可能

    return dis;
}
int main() {
	int x,y;
   while(scanf("%d", &n) != EOF)
    {
        for(int i=0;i<n; i++){
        scanf("%lf %lf", &p[i].x, &p[i].y);
        }
        sort(p, p + n, cmp);
        double result = merge(0, n-1);
        printf("%.4f\n",result);
    }

    return 0;
}
