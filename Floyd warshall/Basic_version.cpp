#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <vector>
#include <queue>

#define	INF		1000000000
#define NODE	10
using namespace std;


// == 플로이드 시작 ==
void  floyd_washall(int graph[NODE][NODE], int* duration_floyd)
{
	clock_t start, finish;
	start = clock();

	int dp[NODE][NODE];
	for (int i = 0; i < NODE; i++)
		for (int j = 0; j < NODE; j++)
			dp[i][j] = graph[i][j];

	// k : 거쳐가는 노드
	for (int k = 0; k < NODE; k++)
		// i : 출발지 노드
		for (int i = 0; i < NODE; i++)
			// j : 도착지 노드
			for (int j = 0; j < NODE; j++)
				// "i -> k , k -> j" 랑  "i -> j" 비교하여 더 작은 값을 선택
				if (dp[i][k] + dp[k][j] < dp[i][j])
					dp[i][j] = dp[i][k] + dp[k][j];

	for (int i = 0; i < NODE; i++)
	{
		for (int j = 0; j < NODE; j++)
		{
			if (dp[i][j] == INF) cout << "-1 ";
			else cout << dp[i][j] << " ";
		}
		cout << '\n';
	}

	finish = clock();
	*duration_floyd = (double)(finish - start);
}
// == 플로이드 끝 ==


// === 다익스트라 시작===
bool visit[NODE];
int dist[NODE];
int min_node;
int get_small_node() {
	// 최소비용노드 탐색 함수
	int min = INF;
	int minpos = 0;
	for (int i = 0; i < NODE; i++) {
		if (dist[i] < min && !visit[i]) {
			min = dist[i];
			minpos = i;
		}
	}
	return minpos;
}

void dijkstra(int start, int graph[NODE][NODE]) {
	for (int i = 0; i < NODE; i++) {
		dist[i] = INF;
		visit[i] = false;
	}

	dist[start] = 0;
	// pair<int, int>	큐에 넣을 자료형 → (거리, 노드번호) 형태
	// vector<pair<int, int>>	내부 컨테이너(기본값도 vector임)
	// greater<pair<int, int>>	정렬 기준 : 작은 값부터 꺼내기(최소 힙)
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0, start });

	while (!pq.empty()) {
		int cur_dist = pq.top().first;
		int cur = pq.top().second;
		pq.pop();

		if (visit[cur]) continue;
		visit[cur] = true;

		for (int next = 0; next < NODE; next++) {
			if (graph[cur][next] != INF) {
				int new_dist = dist[cur] + graph[cur][next];
				if (new_dist < dist[next]) {
					dist[next] = new_dist;
					pq.push({ new_dist, next });
				}
			}
		}
	}
}


void all_dijkstra(int graph[NODE][NODE], int* duration_dijkstra) {
	clock_t start, finish;
	start = clock();

	for (int i = 0; i < NODE; i++)
	{
		dijkstra(i, graph);
		for (int j = 0; j < NODE; j++)
			cout << dist[j] << " ";
		cout << endl;
	}
	cout << endl;
	finish = clock();
	*duration_dijkstra = (double)(finish - start);
}
// === 다익스트라 끝 ===

int main(void)
{	
	cout << "<Basic version>" << endl;
	cout << "주어진 그래프에 대해서 Dijkstra(시작점 1~10변경) vs Floyd 알고리즘의 연산 시간을 측정하시오." << endl;
	int graph[NODE][NODE] = {
		{ 0, 15, 12, INF, INF, INF, INF, INF, INF, INF }, //서울
		{ 15,  0, INF,  INF, INF, 21, INF, 7, INF, INF }, // 원주
		{ 12,  INF, 0, 4, 10, INF, INF, INF, INF, INF }, //천안
		{ INF, INF, 4,   0, 3, INF, 13, INF, INF, INF }, //논산
		{ INF, INF, 10, 3, 0, INF, INF, 10, INF, INF }, //대전
		{ INF, 21, INF, INF, INF, 0, INF, INF, 25, INF }, //강릉
		{ INF, INF, INF, 13, INF, INF, 0, INF, INF, 15 }, //광주
		{ INF, 7, INF, INF, 10, INF, INF, 0, 19, 9 }, //대구
		{ INF, INF, INF, INF, INF, 25, INF, 19, 0, 5 }, //포항
		{ INF, INF, INF, INF, INF, INF, 15, 9, 5, 0 } //부산
	};
	int duration_floyd = 0;
	cout << endl;
	cout << "(floyd_washall 결과)" << endl;
	floyd_washall(graph, &duration_floyd);
	cout << "Floyd-Warshall 알고리즘 연산시간 : " << duration_floyd << " ms" << endl;

	cout << endl;
	int duration_dijkstra = 0;
	cout << "(Dijkstra 결과)" << endl;
	all_dijkstra(graph, &duration_dijkstra);
	cout << "Dijkstra 알고리즘 연산시간 : " << duration_dijkstra << " ms" << endl;


	return 0;
}