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
	// 미구현
}



// 시작 위치와 정점의 개수, 인접 행렬을 받아
// 최소 거리 행렬을 반환함
vector<int> dijkstra(int start, int N, vector<pair<int, int>> graph[])
{
    vector<int> dist(N, INF);  // 거리를 저장할 리스트 초기화
    priority_queue<pair<int, int>> pq;  // 우선순위 큐 선언

    dist[start] = 0;  // 시작 노드 거리를 0으로 함
    pq.push({ 0, start });  // 우선순위 큐에 넣기

    while (!pq.empty())
    {
        int cur_dist = -pq.top().first; // 큐에서 꺼내 방문하고 있는 정점의 거리
        int cur_node = pq.top().second;  // 정점의 인덱스(번호)
        pq.pop();

        for (int i = 0; i < graph[cur_node].size(); i++)
        {
            int nxt_node = graph[cur_node][i].first;  // 인접 정점 번호
            int nxt_dist = cur_dist + graph[cur_node][i].second;  // 인접 정점까지 거리

            if (nxt_dist < dist[nxt_node])  // 지금 계산한 것이 기존 거리값보다 작다면
            {
                dist[nxt_node] = nxt_dist;  // 거리값 업데이트
                pq.push({ -nxt_dist, nxt_node });  // 우선순위 큐에 넣기
            }
        }
    }

    return dist;  // start 노드로부터 각 노드까지 최단거리를 담은 벡터 리턴
}

int main()
{
	vector<Edge> v;
	int vertexCount=0, edgeCount = 0;

	CreateGraph(&v, &vertexCount, &edgeCount);

	cout << "vCount : " << edgeCount << endl;
	

	vector<pair<int, int>> graph[vertexCount];   // 에러1
	int node1=0, node2=0, weight=0;  // 간선의 시작점, 끝점, 가중치
	for (int i = 0; i < vertexCount; i++)
	{
		node1 = v[i].node1;
		node2 = v[i].node2;
		weight = v[i].weight;
		
		graph[node1].push_back({ node2, weight });  // 무향 그래프라 가정하므로 시작점과 끝점 둘 다 벡터에 넣어야 함
		graph[node2].push_back({ node1, weight });
	}

	vector<int> dist = dijkstra(1, vertexCount, graph);
	cout << "끝점까지의 최단거리" << dist[vertexCount - 1] << endl;
    return 0;
}


*/