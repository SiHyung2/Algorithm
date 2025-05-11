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
// �׷��� ���� �Լ�
void CreateGraph(int graph[MAX_NODE][MAX_NODE], int NODE) {
	for (int i = 0; i < NODE; i++) {
		for (int j = 0; j < NODE; j++) {
			graph[i][j] = (i == j) ? 0 : RandomNumber(1, 20);
		}
	}
}


// == �÷��̵� ���� ==
void  floyd_washall(int graph[MAX_NODE][MAX_NODE], int* duration_floyd, int NODE, int dp[MAX_NODE][MAX_NODE])
{
	clock_t start, finish;
	start = clock();

	for (int i = 0; i < NODE; i++)
		for (int j = 0; j < NODE; j++)
			dp[i][j] = graph[i][j];

	// k : ���İ��� ���
	for (int k = 0; k < NODE; k++)
		// i : ����� ���
		for (int i = 0; i < NODE; i++)
			// j : ������ ���
			for (int j = 0; j < NODE; j++)
				// "i -> k , k -> j" ��  "i -> j" ���Ͽ� �� ���� ���� ����
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
// == �÷��̵� �� ==


// === ���ͽ�Ʈ�� ����===
bool visit[MAX_NODE];
int dist[MAX_NODE];
int min_node;

void dijkstra(int start, int graph[MAX_NODE][MAX_NODE], int NODE) {
	for (int i = 0; i < NODE; i++) {
		dist[i] = INF;
		visit[i] = false;
	}

	dist[start] = 0;
	// pair<int, int>	ť�� ���� �ڷ��� �� (�Ÿ�, ����ȣ) ����
	// vector<pair<int, int>>	���� �����̳�(�⺻���� vector��)
	// greater<pair<int, int>>	���� ���� : ���� ������ ������(�ּ� ��)
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
// === ���ͽ�Ʈ�� �� ===

int main(void)
{
	cout << "<Extend version>" << endl;
	cout << "���� �׷����� ���ؼ� Dijkstra vs Floyd �˰����� ���� �ð��� �����Ͻÿ�." << endl;

	int NODE = 20;
	cout << "==============================================" << endl;
	cout << "[����� ������ " << NODE << "�� �����׷����� �����մϴ�...]" << endl;;
	int graph[MAX_NODE][MAX_NODE] = { 0, };
	CreateGraph(graph, NODE);

	int duration_floyd = 0;
	cout << endl;
	cout << "(floyd_washall ���)" << endl;
	int dp[MAX_NODE][MAX_NODE] = { 0, };
	floyd_washall(graph, &duration_floyd, NODE, dp);
	cout << "Floyd-Warshall �˰��� ����ð� : " << duration_floyd << " ms" << endl;

	cout << endl;
	int duration_dijkstra = 0;
	cout << "(Dijkstra ���)" << endl;
	all_dijkstra(graph, &duration_dijkstra, NODE);
	cout << "Dijkstra �˰��� ����ð� : " << duration_dijkstra << " ms" << endl;

	


	int start = -1, end = -1, now = -1, pre=-1, next_min = INF;
	cout << "���� ��� ��ȣ�� �Է��ϼ���(0 ~ " << NODE - 1<< ") : ";
	cin >> start;
	cout << "���� ��� ��ȣ�� �Է��ϼ���(0 ~ " << NODE - 1 << ") : ";
	cin >> end;
	if (start < 0 || start >= NODE || end < 0 || end >= NODE) {
		cout << "�߸��� �Է��Դϴ�." << endl;
		return 0;
	}
		
	cout << "������ �÷��̵� �ͼ� �˰����� �̿��� �ִ� ����Դϴ�." << endl;

	now = start;
	cout << "���: " << now;

	while (now != end) {
		int next = -1;
		for (int j = 0; j < NODE; j++) {
			// �ڱ� �ڽŹ� �������� ���� 
			if (j != now && dp[now][j] + dp[j][end] == dp[now][end]) {
				next = j;
				break;
			}
		}

		if (next == -1) {
			cout << " -> ��� ����";
			break;
		}

		cout << " -> " << next;
		now = next;
	}




	return 0;
}
