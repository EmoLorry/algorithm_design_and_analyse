#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

int father[10000];
int edgeindex[500000];
int weight[500000];
int from[500000];
int to[500000];

struct ListNode {
    int vala;
    int valb;
    ListNode* next;
    ListNode(int x,int y) : vala(x),valb(y),next(NULL) {}
};

// 并查集路径压缩
int findFather(int x) {
    if (x != father[x])
        father[x] = findFather(father[x]);
    return father[x];
}

// 并查集合并
void Union(int a, int b) {
    int faA = findFather(a);
    int faB = findFather(b);
    if (faA != faB)
        father[faA] = faB;
}

// Kruskal算法
int Kruskal(int n, int m) {
    sort(edgeindex, edgeindex + m, [](int a, int b) {
        return weight[a] < weight[b];
    }); // 根据边的权重排序

    int mst_cost = 0;
    int count = 0;
    for (int i = 0; count != n - 1; ++i) {
        int Index = edgeindex[i];
        int faFrom = findFather(from[Index]);
        int faTo = findFather(to[Index]);
        if (faFrom != faTo) {
            Union(from[Index], to[Index]);
            mst_cost += weight[Index];
            count++;
        }
    }
    return mst_cost;
}

int main() {
    int n, m; // n为点的数量，m为边的数量
    int a, b, w;

    while (scanf("%d %d", &n, &m) != EOF){

   
    int** cal_ed = new int*[n];
    for (int i = 0; i < n; ++i) {
        cal_ed[i] = new int[n];
        memset(cal_ed[i], 0, n * sizeof(int));
}

    int** Matrix_heavy = new int*[n];
    for (int i = 0; i < n; ++i) {
        Matrix_heavy[i] = new int[n];
        fill(Matrix_heavy[i], Matrix_heavy[i] + n, 1000);
}

    ListNode* head=NULL;
	for (int i = 0; i < m; i++) {
		if(a>b)
		swap(a,b);
		
        scanf("%d %d %d", &a, &b, &w);
        Matrix_heavy[a][b]=min(w,Matrix_heavy[a][b]);
        if(!cal_ed[a][b])
        {
        	ListNode* tmp=new ListNode(a,b);
            tmp->next=head;
        	head=tmp;
        	cal_ed[a][b]=1;
		}
    }
    int count=0;
    ListNode* temp=head->next;
    while(temp)
    {
    	int a=temp->vala;
    	int b=temp->valb;
    	temp=temp->next;
    	
    	if(a==b)
    	continue;
    	
    	int w=Matrix_heavy[a][b];
    	edgeindex[count] = count;
        weight[count] = w;
        from[count] = a;
        to[count] = b;	
        
		count++;	
	}
    // 初始化并查集
    for (int i = 0; i < n; ++i)
        father[i] = i;

    int result = Kruskal(n, count);
    printf("%d\n", result);
}
    return 0;
}

