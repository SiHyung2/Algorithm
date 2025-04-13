#include <stdio.h>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <random>
#include <limits.h>
using namespace std;

# define INF 99999999


/*

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

void printEdge(vector<Edge> v, int vertexCount) {
	bool isSomenode = false;
	int edgeCount = 0;
	for (auto& i : v) {
		if (isSomenode == false) {
			edgeCount += 1;
			cout << edgeCount << ". random edge : (" << i.node1 << ", " << i.node2 << "), ";
			isSomenode = true;
		}
		else {
			cout << "(" << i.node1 << ", " << i.node2 << ") " << "weight : " << i.weight << endl;
			isSomenode = false;
		}
	}
	cout << endl;
	cout << "Number of Vertices : " << vertexCount << endl;
}

void CreateGraph(vector<Edge>* v, int* vertexCount, int* edgeCount) {
	int node1 = 1, node2 = 1, weight = 1;
	int vertexCount = 0;
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
		(*edgeCount) += 1;
	}

	cout << "Random Matrix Generation!!" << endl;
	printEdge(*v, *vertexCount);
}

void GraphTypeConversion(vector<Edge>* v, vector<pair<int, int>>* graph[]) {
	// �̱���
}



// ���� ��ġ�� ������ ����, ���� ����� �޾�
// �ּ� �Ÿ� ����� ��ȯ��
vector<int> dijkstra(int start, int N, vector<pair<int, int>> graph[])
{
    vector<int> dist(N, INF);  // �Ÿ��� ������ ����Ʈ �ʱ�ȭ
    priority_queue<pair<int, int>> pq;  // �켱���� ť ����

    dist[start] = 0;  // ���� ��� �Ÿ��� 0���� ��
    pq.push({ 0, start });  // �켱���� ť�� �ֱ�

    while (!pq.empty())
    {
        int cur_dist = -pq.top().first; // ť���� ���� �湮�ϰ� �ִ� ������ �Ÿ�
        int cur_node = pq.top().second;  // ������ �ε���(��ȣ)
        pq.pop();

        for (int i = 0; i < graph[cur_node].size(); i++)
        {
            int nxt_node = graph[cur_node][i].first;  // ���� ���� ��ȣ
            int nxt_dist = cur_dist + graph[cur_node][i].second;  // ���� �������� �Ÿ�

            if (nxt_dist < dist[nxt_node])  // ���� ����� ���� ���� �Ÿ������� �۴ٸ�
            {
                dist[nxt_node] = nxt_dist;  // �Ÿ��� ������Ʈ
                pq.push({ -nxt_dist, nxt_node });  // �켱���� ť�� �ֱ�
            }
        }
    }

    return dist;  // start ���κ��� �� ������ �ִܰŸ��� ���� ���� ����
}

int main()
{
	vector<Edge> v;
	int vertexCount=0, edgeCount = 0;

	CreateGraph(&v, &vertexCount, &edgeCount);

	cout << "vCount : " << edgeCount << endl;
	

	vector<pair<int, int>> graph[vertexCount];   // ����1
	int node1=0, node2=0, weight=0;  // ������ ������, ����, ����ġ
	for (int i = 0; i < vertexCount; i++)
	{
		node1 = v[i].node1;
		node2 = v[i].node2;
		weight = v[i].weight;
		
		graph[node1].push_back({ node2, weight });  // ���� �׷����� �����ϹǷ� �������� ���� �� �� ���Ϳ� �־�� ��
		graph[node2].push_back({ node1, weight });
	}

	vector<int> dist = dijkstra(1, vertexCount, graph);
	cout << "���������� �ִܰŸ�" << dist[vertexCount - 1] << endl;
    return 0;
}


*/