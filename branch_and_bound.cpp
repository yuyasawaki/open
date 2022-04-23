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
typedef pair<int, int> Link; // �����N�̌^ Link �̒�`
map<Link, int> cost; // �����N�̃R�X�g�Ɋւ���A�z�z��
Link link(int a, int b) { return make_pair(a, b); };


// parameter
const int MAX_V = 1000;
std::vector<int> graph[MAX_V];
int g[MAX_V];
int parent[MAX_V];
int root[MAX_V][3];
int a;

int main() {
	
	// �T���؂̍쐬
	gen_graph();

	// ���}����@�̎��s
	branch_and_bound(1, 7);

	// �T���o�H�̃��O��\��
	printf("start --> ");
	for (int i = 1; i<=a; i++) printf("%d(%d,%d) --> ", root[i][0],root[i][1],root[i][2]);
	printf("end\n");

	return 0;
}

bool include(std::deque<int>& q, int n) {
	return q.end() != find(q.begin(), q.end(), n);
}


void gen_graph() {
	
	//�e�m�[�h�̎q�m�[�h��ݒ�
	graph[1] = vector<int>{ 2, 3, 4 };
	graph[2] = vector<int>{ 5, 6 };
	graph[3] = vector<int>{ 2, 4, 7 };
	graph[4] = vector<int>{ 7 };
	graph[5] = vector<int>{ 6 };
	graph[6] = vector<int>{ 3, 7 };
	
	//�e�����N�̃R�X�g��ݒ�
	cost[link(1, 2)] = 3; cost[link(1, 3)] = 2; cost[link(1, 4)] = 4;
	cost[link(2, 5)] = 2; cost[link(2, 6)] = 1;
	cost[link(3, 2)] = 1; cost[link(3, 4)] = 2; cost[link(3, 7)] = 5;
	cost[link(4, 7)] = 3;
	cost[link(5, 6)] = 3;
	cost[link(6, 3)] = 1; cost[link(6, 7)] = 2;

}

//Link(a,b)�̃R�X�g��Ԃ�
int c(int a, int b) {

	Link l(a, b);
	if (cost.find(l) != cost.end()) return cost[l];

	return INT_MAX;
}

void branch_and_bound(int start, int goal) {
	
	
	deque<int> open({ start }), closed;
	g[start] = 0;
	
	while (!open.empty()) { // open ����łȂ�

		// open �̐擪�v�f�����o��
		int n = open.front(); open.pop_front();

		root[a][0] = n;
		root[a][1] = parent[n];
		root[a][2] = n;
		if (n == goal) return;


		// n ��closed �ɒǉ�
		closed.push_back(n);

		// n �̎q�m�[�h�̃��X�g���t���ɂ���
		vector<int> L = graph[n];
		reverse(L.begin(), L.end());
		
		
		for (int m : L) { // n �̊e�q�m�[�hm �ɂ���
			// m ��open �ɂ�closed �ɂ��܂܂�Ȃ��Ƃ�
			if (!include(open, m) && !include(closed, m)) {
				g[m] = g[n] + c(n, m);
				parent[m] = n;
				// m ��open �̐擪�ɒǉ�
				open.push_front(m);
			}
			// m ��open �Ɋ܂܂��Ƃ�
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

