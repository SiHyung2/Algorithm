

## 번외.📌 연산자 오버로딩 & 객체참조 ##


### 💠연산자 오버로딩 ###
 - operator< 라는 함수는 < 연산자를 오버로딩한다는 뜻
- 예
   - 아래의 코드를 보며 사용법을 확인


### 💠객체 참조 ###
- 참조 : 메모리 주소를 직접 사용하여 객체를 다루는 방법. 원본값이 바뀌면 참조값도 바뀜
- 예
  -  (const Edge & edge) 설명
  - 아래의 코드를 참고

```
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
	bool operator<(const Edge& edge) const {
		return this->distance < edge.distance;
	}
};
```
