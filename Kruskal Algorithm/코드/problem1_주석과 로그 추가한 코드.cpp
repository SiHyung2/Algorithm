#include <stdio.h>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>

using namespace std;

random_device rd;
mt19937_64 rng(rd());
template<typename T>
T RandomNumber(T start, T end) {
	uniform_int_distribution<T> dist(start, end);
	return dist(rng);
}


int check[7];	//��� �����, �����尡 �ٲ���� üũ 

class Edge {
public:
	int node[2];
	int distance;
	Edge(int a, int b, int distance) {
		this->node[0] = a;
		this->node[1] = b;
		this->distance = distance;
	}

	// ������ ������������ �����Ҷ� ������ distance�� �����ݴϴ�. 
	// 
	// �̺κ��� �Լ� ���� �κ���
	// ������ �����ε�
	//    - operator< ��� �Լ��� < �����ڸ� �����ε��Ѵٴ� ��
	//    - ����
	//			Edge a(1, 2, 5);
	//			Edge b(2, 3, 3);
	//          if (a<b) { ... }
	//          ====> a<b�� ����ϸ� Edge Ŭ������ operator< �Լ��� ȣ���
	//                operator< �Լ������� �ڵ嵵 �����
	//				  �����δ� a.operator<(b);  �� ����Ǵ� ����
	//
	// (const Edge & edge) ����
	//    - ���
	//       - const Edge & �� Ÿ�� �����̰� edge�� ������
	//    - �ܰ躰 ����
	//      1. Edge edge   
	//		   - ���� �⺻��
	//         - Edge ��ü�� edge�̸����� ����
	//      2. Edge& edge
	//         - ��ü ������ �ٲ��
	//	    3. const Edge& edge
	//         - �б� ���� ������. �������� �ٲ��� �������� �ٲ����ʵ��� �������� �߰��� ��
	//     - �߰� ����
	//         - ����(reference) : �޸� �ּҸ� ���� ����Ͽ� ��ü�� �ٷ�� ���. �������� �ٲ�� �������� �ٲ�.
	//         - const : ���, �������� �ٲ��� �ʵ��� �ϴ� ��. ���⼭�� const�� �ٿ��� �������� �ٲ��� �ʵ��� ��
	bool operator<(const Edge & edge) const {
		return this->distance < edge.distance;
	}
};

int getParent(int node) {
	if (check[node] == node) return node;
	return getParent(check[node]);
}

//�� ��带 �������� �������� �����մϴ�. 
void unionParent(int node1, int node2) {
	node1 = getParent(node1);
	node2 = getParent(node2);
	if (node1 < node2) check[node2] = node1;
	else check[node1] = node2;
}

//����Ŭ�� �����ϸ� true, �ƴϸ� false�� ��ȯ
bool isCycle(int node1, int node2) {
	node1 = getParent(node1);
	node2 = getParent(node2);
	if (node1 == node2) return true;
	else return false;
}

int main() {
	vector<Edge> v;

	int node1 = 1, node2 = 1, weight = 1;
	int duplicationCheck[11][11]= {0,};
	int vertex[11] = {0,};
	int vertexCount = 0;

	node1 = RandomNumber(1, 10);
	node2 = RandomNumber(1, 10);
	while(vertexCount < 10) {
		if(RandomNumber(0,1)){
			node1 = node2;
		}

		node2 = RandomNumber(1, 10);
		while (node1 == node2) {
			node2 = RandomNumber(1, 10);
		}
		weight = RandomNumber(1, 20);


		if (duplicationCheck[node1][node2] == 1 || duplicationCheck[node2][node1] == 1) {
		}

		if(vertex[node1] == 0) {
			vertex[node1] = 1;
			vertexCount += 1;
			cout << "New vertec : " << node1 << endl;
		}

		if (vertex[node2] == 0) {
			vertex[node2] = 1;
			vertexCount += 1;
			cout << "New vertec : " << node2 << endl;
		}

		cout << "node1 : " << node1 << " node2 : " << node2 << " weight : " << weight << "    vertecCount : " << vertexCount << endl;
		
		duplicationCheck[node1][node2] = 1;
		v.push_back(Edge(node1, node2, weight));
		v.push_back(Edge(node2, node1, weight));

	}

	return 0;
}