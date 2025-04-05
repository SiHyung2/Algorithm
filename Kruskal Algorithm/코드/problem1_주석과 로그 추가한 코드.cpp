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


int check[7];	//노드 연결용, 연결노드가 바뀌는지 체크 

class Edge {
public:
	int node[2];
	int distance;
	Edge(int a, int b, int distance) {
		this->node[0] = a;
		this->node[1] = b;
		this->distance = distance;
	}

	// 간선을 오름차순으로 정렬할때 기준을 distance로 정해줍니다. 
	// 
	// 이부분은 함수 선언 부분임
	// 연산자 오버로딩
	//    - operator< 라는 함수는 < 연산자를 오버로딩한다는 뜻
	//    - 예시
	//			Edge a(1, 2, 5);
	//			Edge b(2, 3, 3);
	//          if (a<b) { ... }
	//          ====> a<b를 사용하면 Edge 클래스의 operator< 함수가 호출됨
	//                operator< 함수내부의 코드도 실행됨
	//				  실제로는 a.operator<(b);  가 실행되는 것임
	//
	// (const Edge & edge) 설명
	//    - 요약
	//       - const Edge & 이 타입 선언이고 edge이 변수명
	//    - 단계별 설명
	//      1. Edge edge   
	//		   - 원래 기본형
	//         - Edge 객체를 edge이름으로 선언
	//      2. Edge& edge
	//         - 객체 참조로 바뀐것
	//	    3. const Edge& edge
	//         - 읽기 전용 참조형. 참조값이 바껴도 원본값이 바뀌지않도록 안정성을 추가한 것
	//     - 추가 설명
	//         - 참조(reference) : 메모리 주소를 직접 사용하여 객체를 다루는 방법. 원본값이 바뀌면 참조값도 바뀜.
	//         - const : 상수, 원본값이 바뀌지 않도록 하는 것. 여기서는 const를 붙여서 원본값이 바뀌지 않도록 함
	bool operator<(const Edge & edge) const {
		return this->distance < edge.distance;
	}
};

int getParent(int node) {
	if (check[node] == node) return node;
	return getParent(check[node]);
}

//두 노드를 작은값을 기준으로 연결합니다. 
void unionParent(int node1, int node2) {
	node1 = getParent(node1);
	node2 = getParent(node2);
	if (node1 < node2) check[node2] = node1;
	else check[node1] = node2;
}

//싸이클이 존재하면 true, 아니면 false를 반환
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