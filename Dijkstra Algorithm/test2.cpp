#include <iostream>
#include <vector>
#include <queue>
#include <random>
#include <limits.h>
#include <algorithm>
using namespace std;

#define INF 99999999

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
        if (!isSomenode) {
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
    int duplicationCheck[11][11] = { 0, };
    int vertex[11] = { 0, };

    while (*vertexCount < 10) {
        if (RandomNumber(0, 1))
            node1 = node2;
        node2 = RandomNumber(1, 10);
        while (node1 == node2) {
            node2 = RandomNumber(1, 10);
        }
        weight = RandomNumber(1, 20);

        if (duplicationCheck[node1][node2]) continue;

        if (!vertex[node1]) {
            vertex[node1] = 1;
            (*vertexCount)++;
        }
        if (!vertex[node2]) {
            vertex[node2] = 1;
            (*vertexCount)++;
        }

        duplicationCheck[node1][node2] = duplicationCheck[node2][node1] = 1;

        v->push_back(Edge(node1, node2, weight));
        v->push_back(Edge(node2, node1, weight));
        (*edgeCount)++;
    }

    cout << "Random Matrix Generation!!" << endl;
    printEdge(*v, *vertexCount);
}

pair<vector<int>, vector<int>> dijkstra(int start, int N, vector<vector<pair<int, int>>>& graph) {
    vector<int> dist(N + 1, INF);
    vector<int> prev(N + 1, -1);
    priority_queue<pair<int, int>> pq;

    dist[start] = 0;
    pq.push({ 0, start });

    while (!pq.empty()) {
        int cur_dist = -pq.top().first;
        int cur_node = pq.top().second;
        pq.pop();

        if (cur_dist > dist[cur_node]) continue;

        for (auto& next : graph[cur_node]) {
            int nxt_node = next.first;
            int nxt_dist = cur_dist + next.second;

            if (nxt_dist < dist[nxt_node]) {
                dist[nxt_node] = nxt_dist;
                prev[nxt_node] = cur_node;
                pq.push({ -nxt_dist, nxt_node });
            }
        }
    }

    return { dist, prev };
}

void printPath(int target, const vector<int>& prev, const vector<int>& dist) {
    vector<int> path;
    int cur = target;
    while (cur != -1) {
        path.push_back(cur);
        cur = prev[cur];
    }
    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); ++i) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << " (Cost: " << dist[target] << ")" << endl;
}

int main() {
    vector<Edge> v;
    int vertexCount = 0, edgeCount = 0;

    CreateGraph(&v, &vertexCount, &edgeCount);

    cout << "vCount : " << edgeCount << endl;

    int maxNode = 10;
    vector<vector<pair<int, int>>> graph(maxNode + 1);

    for (const auto& edge : v) {
        graph[edge.node1].push_back({ edge.node2, edge.weight });
    }

    int start = 1;
    pair<vector<int>, vector<int>> result = dijkstra(start, maxNode, graph);
    vector<int> dist = result.first;
    vector<int> prev = result.second;


    cout << "\n[1번 정점에서 다른 모든 정점까지의 최단 경로]\n";
    for (int i = 1; i <= maxNode; ++i) {
        if (i != start && dist[i] != INF) {
            printPath(i, prev, dist);
        }
    }

    return 0;
}