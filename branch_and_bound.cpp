#include <stdio.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace std;

int count=0;

// functiohn
void gen_graph();
void branch_and_bound(int start, int goal);
int c(int a,int b);
bool include(std::deque<int>& q, int n);


// structure
typedef pair<int, int> Link; // リンクの型 Link の定義
map<Link, int> cost; // リンクのコストに関する連想配列
Link link(int a, int b) { return make_pair(a, b); };


// parameter
const int MAX_V = 1000;
std::vector<int> graph[MAX_V];
int g[MAX_V];
int parent[MAX_V];
int root[MAX_V][3];
int a;

int main() {
	
	// 探索木の作成
	gen_graph();

	// 分枝限定法の実行
	branch_and_bound(1, 7);

	// 探索経路のログを表示
	printf("start --> ");
	for (int i = 1; i<=a; i++) printf("%d(%d,%d) --> ", root[i][0],root[i][1],root[i][2]);
	printf("end\n");

	return 0;
}

bool include(std::deque<int>& q, int n) {
	return q.end() != find(q.begin(), q.end(), n);
}


void gen_graph() {
	
	//各ノードの子ノードを設定
	graph[1] = vector<int>{ 2, 3, 4 };
	graph[2] = vector<int>{ 5, 6 };
	graph[3] = vector<int>{ 2, 4, 7 };
	graph[4] = vector<int>{ 7 };
	graph[5] = vector<int>{ 6 };
	graph[6] = vector<int>{ 3, 7 };
	
	//各リンクのコストを設定
	cost[link(1, 2)] = 3; cost[link(1, 3)] = 2; cost[link(1, 4)] = 4;
	cost[link(2, 5)] = 2; cost[link(2, 6)] = 1;
	cost[link(3, 2)] = 1; cost[link(3, 4)] = 2; cost[link(3, 7)] = 5;
	cost[link(4, 7)] = 3;
	cost[link(5, 6)] = 3;
	cost[link(6, 3)] = 1; cost[link(6, 7)] = 2;

}

//Link(a,b)のコストを返す
int c(int a, int b) {

	Link l(a, b);
	if (cost.find(l) != cost.end()) return cost[l];

	return INT_MAX;
}

void branch_and_bound(int start, int goal) {
	
	
	deque<int> open({ start }), closed;
	g[start] = 0;
	
	while (!open.empty()) { // open が空でない

		// open の先頭要素を取り出す
		int n = open.front(); open.pop_front();

		root[a][0] = n;
		root[a][1] = parent[n];
		root[a][2] = n;
		if (n == goal) return;


		// n をclosed に追加
		closed.push_back(n);

		// n の子ノードのリストを逆順にする
		vector<int> L = graph[n];
		reverse(L.begin(), L.end());
		
		
		for (int m : L) { // n の各子ノードm について
			// m がopen にもclosed にも含まれないとき
			if (!include(open, m) && !include(closed, m)) {
				g[m] = g[n] + c(n, m);
				parent[m] = n;
				// m をopen の先頭に追加
				open.push_front(m);
			}
			// m がopen に含まれるとき
			else if (include(open, m)) {
				if (g[n] + c(n, m) < g[m]) {
					g[m] = g[n] + c(n, m);
					parent[m] = n;
				}
			}
		}

		sort(open.begin(), open.end(), [](int a, int b) { return g[a] < g[b]; });
		
		a++;
	}
	
}

