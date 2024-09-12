#include <iostream>
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
    double dis = 1e20; // ��ʼ������
    if (left == right) // �ݹ����
        return dis;

    if (left + 1 == right)
        return distance(left, right);

    int mid = (left + right) / 2;
    double d1 = merge(left, mid);
    double d2 = merge(mid + 1, right);
    dis = min(d1, d2);

    int k = 0;
    // ���п��ܸ����ĵ��¼����
    for (int i = left; i <= right; ++i) {
        if (fabs(p[i].x - p[mid].x) <= dis)
            temp[k++] = i;
    }

    // ����y��������
    sort(temp, temp + k, [&](int a, int b) { return cmds(a, b); });

    for (int i = 0; i < k; ++i) // ö���ҵ���С����
        for (int j = i + 1; j < k && p[temp[j]].y - p[temp[i]].y < dis; ++j)
            dis = min(dis, distance(temp[i], temp[j])); // �����ֿ���

    return dis;
}

int main() {
    ifstream inputFile("in_merge.txt");
    ofstream outputFile("out_merge.txt");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    while (inputFile >> n) {
        for (int i = 0; i < n; i++)
            inputFile >> p[i].x >> p[i].y;

        sort(p, p + n, cmp); // ����x��������
        outputFile << fixed << merge(0, n - 1) << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}
