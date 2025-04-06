#include <stdio.h>
#include <vector>
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
};


void printEdge(vector<Edge> v, int vertexCount) {
	bool isSomenode = false;
	int edgeCount = 1;
	for (auto& i : v) {
		if (isSomenode == false) {
			cout << edgeCount << ". random edge : (" << i.node1 << ", " << i.node2 << "), ";
			isSomenode = true;
			edgeCount += 1;
		}
		else {
			cout << "(" << i.node1 << ", " << i.node2 << ") " << "weight : " << i.weight << endl;
			isSomenode = false;
		}
	}
	cout << endl;
	cout << "Number of Vertices : " << vertexCount << endl;
	cout << "Number of Edges : " << edgeCount << endl;
}


void printMatrixGraph(vector<Edge> v, int vertexCount) {

	int node1=0, node2=0, weight=0;
	int matrix[11][11] = { 0, };

	for (auto& i : v) {
		node1 = i.node1;
		node2 = i.node2;
		weight = i.weight;
		matrix[node1][node2] = weight;
	}


	cout << endl;
	cout << "Adjacency Matrix of Direct Graph" << endl;
	for (int i = 1; i <= vertexCount; i++) {
		for (int j = 1; j <= vertexCount; j++) {
			
			if (matrix[i][j] == 0)
				cout << "  0";
			else if(matrix[i][j] < 10)
				cout << "  " << matrix[i][j];
			else if (matrix[i][j] >= 10)
				cout << " "  << matrix[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void CreateGraph(vector<Edge>* v, int* vertexCount) {
	int node1 = 1, node2 = 1, weight = 1;
	int duplicationCheck[11][11] = { 0, };
	int vertex[11] = { 0, };

	node1 = RandomNumber(1, 10);
	node2 = RandomNumber(1, 10);

	while (*vertexCount < 10) {
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
			*vertexCount += 1;
		}
		if (vertex[node2] == 0) {
			vertex[node2] = 1;
			*vertexCount += 1;
		}
		duplicationCheck[node1][node2] = 1;
		duplicationCheck[node2][node1] = 1;


		
		(*v).push_back(Edge(node1, node2, weight));
		(*v).push_back(Edge(node2, node1, weight));

	}

	cout << "Random Matrix Generation!!" << endl;
	printEdge(*v, *vertexCount);
}


int main() {
	vector<Edge> v;

	int vertexCount = 0;

	CreateGraph(&v, &vertexCount);
	printMatrixGraph(v, vertexCount);

	return 0;
}