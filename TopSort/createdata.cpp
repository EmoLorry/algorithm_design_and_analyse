#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <cstdlib> // 包含 rand 和 srand 函数

using namespace std;
int main() {
    const int NODES = 5;
    const int EDGES = 8;
    srand(time(NULL)); // 初始化随机种子 
    int desc[NODES];
    for(int i=0;i!=NODES;i++)
    desc[i]=i;
    
    srand(unsigned(time(NULL)));

    // 使用 random_shuffle 函数对数组进行乱序
    random_shuffle(desc, desc+NODES);
	for(int i=0;i!=NODES;i++)
	cout<<desc[i]<<" ";
	
	
	
	vector<pair<int, int> > edges;

    for (int i = 0; i < EDGES; ++i) {
        int from = rand() % NODES;
        int to = from + 1 + rand() % (NODES - from - 1);
        
        if(to>NODES-1) 
            i--;
        else
        	edges.push_back({from, to});
      
    }

    ofstream outFile("caizihuan_luorui2.txt");
    if (!outFile.is_open()) {
        cerr << "Failed to open file for writing." << endl;
        return -1;
    }
    // 写入边信息到文件
for (int i = 0; i != EDGES; ++i) {
    outFile << desc[edges[i].first] << " " << desc[edges[i].second] << endl;
}

    outFile.close();
    return 0;
}
