#include <iostream>
#include <ctime>
#include <algorithm>
#include <random>
#include <vector>
#include <queue>

#define	INF		1000000000
#define MAX_NODE 20
using namespace std;

random_device rd;
mt19937_64 rng(rd());

template<typename T>
T RandomNumber(T start, T end) {
	uniform_int_distribution<T> dist(start, end);
	return dist(rng);
}
// 그래프 생성 함수
void CreateGraph(int graph[MAX_NODE][MAX_NODE], int NODE) {
	for (int i = 0; i < NODE; i++) {
		for (int j = 0; j < NODE; j++) {
			graph[i][j] = (i == j) ? 0 : RandomNumber(1, 20);
		}
	}
}


// == 플로이드 시작 ==
void  floyd_washall(int graph[MAX_NODE][MAX_NODE], int* duration_floyd, int NODE, int dp[MAX_NODE][MAX_NODE])
{
	clock_t start, finish;
	start = clock();

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
bool visit[MAX_NODE];
int dist[MAX_NODE];
int min_node;

void dijkstra(int start, int graph[MAX_NODE][MAX_NODE], int NODE) {
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


void all_dijkstra(int graph[MAX_NODE][MAX_NODE], int* duration_dijkstra, int NODE) {
	clock_t start, finish;
	start = clock();

	for (int i = 0; i < NODE; i++)
	{
		dijkstra(i, graph, NODE);
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
	cout << "<Extend version>" << endl;
	cout << "랜덤 그래프에 대해서 Dijkstra vs Floyd 알고리즘의 연산 시간을 측정하시오." << endl;

	int NODE = 20;
	cout << "==============================================" << endl;
	cout << "[노드의 개수가 " << NODE << "인 랜덤그래프를 생성합니다...]" << endl;;
	int graph[MAX_NODE][MAX_NODE] = { 0, };
	CreateGraph(graph, NODE);

	int duration_floyd = 0;
	cout << endl;
	cout << "(floyd_washall 결과)" << endl;
	int dp[MAX_NODE][MAX_NODE] = { 0, };
	floyd_washall(graph, &duration_floyd, NODE, dp);
	cout << "Floyd-Warshall 알고리즘 연산시간 : " << duration_floyd << " ms" << endl;

	cout << endl;
	int duration_dijkstra = 0;
	cout << "(Dijkstra 결과)" << endl;
	all_dijkstra(graph, &duration_dijkstra, NODE);
	cout << "Dijkstra 알고리즘 연산시간 : " << duration_dijkstra << " ms" << endl;

	


	int start = -1, end = -1, now = -1, pre=-1, next_min = INF;
	cout << "시작 노드 번호를 입력하세요(0 ~ " << NODE - 1<< ") : ";
	cin >> start;
	cout << "도착 노드 번호를 입력하세요(0 ~ " << NODE - 1 << ") : ";
	cin >> end;
	if (start < 0 || start >= NODE || end < 0 || end >= NODE) {
		cout << "잘못된 입력입니다." << endl;
		return 0;
	}
		
	cout << "다음은 플로이드 와샬 알고리즘을 이용한 최단 경로입니다." << endl;

	now = start;
	cout << "경로: " << now;

	while (now != end) {
		int next = -1;
		for (int j = 0; j < NODE; j++) {
			// 자기 자신및 역방향은 제외 
			if (j != now && dp[now][j] + dp[j][end] == dp[now][end]) {
				next = j;
				break;
			}
		}

		if (next == -1) {
			cout << " -> 경로 없음";
			break;
		}

		cout << " -> " << next;
		now = next;
	}




	return 0;
}
