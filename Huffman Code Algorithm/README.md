## 1\. 개요

-   sample.txt 파일을 읽어 허프만 코딩 알고리즘을 통해
    -   문자 빈도 분석
    -   허프만 트리 구성
    -   인코딩 및 디코딩
    -   압축률 계산
-   **목표** : 압축 전후를 비교하고, 원본 복구를 정확히 수행한다.

---

## 2\. 프로그램 동작 순서

### \[1\] HuffmanTree 객체 생성

-   T 객체 생성 시 멤버(root, ascii, code, pq) 초기화

### \[2\] Start() 호출: 파일 읽기 → 빈도 집계 → 트리 구성 → 코드 생성

-   ifstream으로 sample.txt 열기
-   getline()으로 한 줄씩 읽고 문자 빈도수 카운트 (+ 줄바꿈 \\n 포함)
-   빈도수 맵을 기반으로 우선순위 큐에 노드 삽입
-   MakeTree() 호출 → 가장 작은 빈도 노드 2개를 합쳐 트리 생성
-   FindTree() 호출 → 리프 노드마다 허프만 코드 매핑

### \[3\] 허프만 코드 출력

-   문자별 허프만 코드 출력

### \[4\] 파일 인코딩

-   sample.txt를 읽고 대응되는 허프만 코드로 변환
-   sample.enc 파일에 인코딩 결과 저장

### \[5\] 파일 디코딩

-   sample.enc 파일을 읽어 허프만 트리로 복원
-   sample.dec 파일로 출력

### \[6\] 디코드 파일과 원본 비교

-   sample.txt 와 sample.dec 파일을 줄 단위로 비교
-   일치 여부 확인

### \[7\] 압축률 계산

-   원본 파일과 압축 파일의 비트 수를 비교
-   압축률(%) 출력

---

## 3\. 주요 기술 및 문법 설명

### 💠 소멸자 (~HuffmanTree)

-   프로그램 종료 시 자동 호출
-   트리 메모리 해제
-   root를 nullptr로 초기화
-   우선순위 큐 비우기

### 💠 private 멤버

-   huffmanNode\* root : 트리 루트 포인터
-   unordered\_map<char, int> ascii : 문자 빈도수 저장
-   unordered\_map<char, string> code : 문자별 허프만 코드 저장

### 💠 우선순위 큐 (priority\_queue)

-   목적: 빈도가 작은 노드를 먼저 꺼내기
-   선언: priority\_queue<구조체명\*, vector<구조체명\*>, cmp>
-   비교자 cmp를 통해 fre 작은 노드가 먼저 나오도록 설정
-   주요 메소드: push(), pop(), top()

---

## 4\. 주요 함수 설명

함수명설명

| Start() | 파일 읽기, 빈도수 집계, 트리 생성, 코드 생성 |
| --- | --- |
| MakeTree() | 허프만 트리 구성 (우선순위 큐 이용) |
| FindTree() | 리프 노드까지 내려가며 허프만 코드 매핑 |
| showCode() | 허프만 코드 출력 |
| encodeFile() | 파일을 허프만 코드로 인코딩 |
| decodeFile() | 인코딩된 파일을 디코딩하여 원본 복구 |
| verifyFile() | 디코딩 파일과 원본 파일 비교 |
| compressionStats() | 압축률 계산 및 출력 |
