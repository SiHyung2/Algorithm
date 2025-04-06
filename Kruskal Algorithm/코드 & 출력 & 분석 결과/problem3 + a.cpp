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

class Edge {
public:
	int node1, node2;
	int weight;
	Edge(int node1, int node2, int weight) {
		this->node1 = node1;
		this->node2 = node2;
		this->weight = weight;
	}

	bool operator<(const Edge& edge) const {
		return this->weight < edge.weight;
	}
};



void printEdge(vector<Edge> v) {
	for (int i = 0;i < v.size();++i) {
		cout << " edge : (" << v[i].node1 << ", " << v[i].node2 << ") " << endl;
	}
	cout << endl;
}


void printEdge2(vector<Edge> v, int vertexCount) {
	bool isSomenode = false;
	int edgeCount = 1;
	for (int i = 0;i < v.size();++i) {
		if (isSomenode == false) {
			cout << edgeCount << ". random edge : (" << v[i].node1 << ", " << v[i].node2 << "), ";
			isSomenode = true;
			edgeCount += 1;
		}
		else {
			cout << "(" << v[i].node1 << ", " << v[i].node2 << ") " << "weight : " << v[i].weight << endl;
			isSomenode = false;
		}
	}
	cout << endl;
	cout << "Number of Vertices : " << vertexCount << endl;
	cout << "Number of Edges : " << edgeCount << endl;
}



int check[11];

int getParent(int node) {
	if (check[node] == node)
		return node;
	return getParent(check[node]);
}

void unionParent(int node1, int node2) {
	node1 = getParent(node1);
	node2 = getParent(node2);
	if (node1 < node2)
		check[node2] = node1;
	else
		check[node1] = node2;
}

bool isCycle(int node1, int node2) {
	node1 = getParent(node1);
	node2 = getParent(node2);
	if (node1 == node2) return true;
	else return false;
}


void CreateGraph(vector<Edge>* v) {
	int node1 = 1, node2 = 1, weight = 1;
	int vertexCount = 0;
	int duplicationCheck[11][11] = { 0, };
	int vertex[11] = { 0, };

	node1 = RandomNumber(1, 10);
	node2 = RandomNumber(1, 10);

	while (vertexCount < 10) {
		if (RandomNumber(0, 1))
			node1 = node2;
		else
			node1 = node1;

		node2 = RandomNumber(1, 10);
		while (node1 == node2) {
			node2 = RandomNumber(1, 10);
		}
		weight = RandomNumber(1, 20);


		if (duplicationCheck[node1][node2] == 1)
			continue;

		if (vertex[node1] == 0) {
			vertex[node1] = 1;
			vertexCount += 1;
		}
		if (vertex[node2] == 0) {
			vertex[node2] = 1;
			vertexCount += 1;
		}
		duplicationCheck[node1][node2] = 1;
		duplicationCheck[node2][node1] = 1;



		(*v).push_back(Edge(node1, node2, weight));
		(*v).push_back(Edge(node2, node1, weight));

	}

	cout << "Random Matrix Generation!!" << endl;
	printEdge2(*v, vertexCount);
}


int main() {
	vector<Edge> v;
	vector<Edge> mst;

	CreateGraph(&v);

	

	for (int i = 1;i <= 10;++i) {
		check[i] = i;
	}

	int sum = 0;
	cout << endl;
	for (int i = 0;i < v.size();++i) {
		if(i==0) {
			cout << "첫번째 생성된 edge : (" << v[i].node1 << ", " << v[i].node2 << ") " << "는 반드시 포함됩니다" << endl;
			sum += v[i].weight;
			unionParent(v[i].node1, v[i].node2);
			mst.push_back(v[i]);
		}
		else if (!isCycle(v[i].node1, v[i].node2)) {
			sum += v[i].weight;
			unionParent(v[i].node1, v[i].node2);
			mst.push_back(v[i]);
		}
	}

	sort(v.begin(), v.end());
	cout << "Minimum Cost : " << sum << endl;
	cout << "Minimum Spanning Tree" << endl;
	printEdge(mst);

	return 0;
}