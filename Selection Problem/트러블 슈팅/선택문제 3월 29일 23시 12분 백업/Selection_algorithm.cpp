#include <iostream>
#include <random>


using namespace std;


int RandomNumber(int start, int end) {
    random_device rd;
    mt19937_64 rng(rd());

    uniform_int_distribution<__int64> dist(start, end);
    int number = dist(rng);

    return number;
}

// 스왑 함수 (2차원 배열)
void SwapArray_2d(int** arr, int row1, int col1, int row2, int col2) {
    int temp = arr[row1][col1];
    arr[row1][col1] = arr[row2][col2];
    arr[row2][col2] = temp;
}

// 3-Way QuickSort
void ThreePartQuickSort(int** arr_2d, int colMaxIndex, int startRow, int startCol, int endRow, int endCol, int* p_comparisonCount) {

    int startIdx = startRow * colMaxIndex + startCol;
    int endIdx = endRow * colMaxIndex + endCol;

    if (startIdx >= endIdx) return;

    int pivotIdx = (startIdx + endIdx) / 2;
    int pivotRow = pivotIdx / colMaxIndex;
    int pivotCol = pivotIdx % colMaxIndex;
    int pivot = arr_2d[pivotRow][pivotCol];

    int left = startIdx;
    int mid = startIdx;
    int right = endIdx;

    while (mid <= right) {
        int midRow = mid / colMaxIndex;
        int midCol = mid % colMaxIndex;
        int val = arr_2d[midRow][midCol];
        (*p_comparisonCount)++;

        if (val < pivot) {
            int leftRow = left / colMaxIndex;
            int leftCol = left % colMaxIndex;
            SwapArray_2d(arr_2d, leftRow, leftCol, midRow, midCol);
            left++;
            mid++;
        }
        else if (val > pivot) {
            int rightRow = right / colMaxIndex;
            int rightCol = right % colMaxIndex;
            SwapArray_2d(arr_2d, midRow, midCol, rightRow, rightCol);
            right--;
        }
        else {
            mid++;
        }
    }

    // 왼쪽 정렬
    if (left > startIdx) {
        int leftRow = (left - 1) / colMaxIndex;
        int leftCol = (left - 1) % colMaxIndex;
        ThreePartQuickSort(arr_2d, colMaxIndex, startRow, startCol, leftRow, leftCol, p_comparisonCount);
    }

    // 오른쪽 정렬
    if (right < endIdx) {
        int rightRow = (right + 1) / colMaxIndex;
        int rightCol = (right + 1) % colMaxIndex;
        ThreePartQuickSort(arr_2d, colMaxIndex, rightRow, rightCol, endRow, endCol, p_comparisonCount);
    }
}

/*
void Selection(int** arr_2d, int colMaxIndex, int startRow, int startCol, int endRow, int endCol, int* p_comparisonCount2) {

    int startIdx = startRow * colMaxIndex + startCol;
    int endIdx = endRow * colMaxIndex + endCol;

    if (startIdx >= endIdx) return;

    int pivotIdx = (startIdx + endIdx) / 2;
    int pivotRow = pivotIdx / colMaxIndex;
    int pivotCol = pivotIdx % colMaxIndex;
    int pivot = arr_2d[pivotRow][pivotCol];

    int left = startIdx;
    int mid = startIdx;
    int right = endIdx;



    //선택 문제 알고리즘 작성하고.. 비교횟수도 계산해야함.
}

*/
int main() {

    // 1. 500~1,000 사이의 입력값 n을 받으시오.
    int n = RandomNumber(500, 1000);

    // 2. n x n 크기의 이차원 배열을 만들고 1~100,000 사이의 랜덤값으로 채우시오.
    int rows = n, cols = n;
    int** arr = new int* [rows];
    int** arr2 = new int* [rows];
    int randomData = 0;
    int temp = 0;
    for (int i = 0; i < rows; ++i) {
        arr[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            randomData = RandomNumber(1, 100000);
            arr[i][j] = randomData;
            
            여기서 이상하게 에러가 나!! 하... arr2[i][j] = 1;
        }
    }
    cout << "n: " << n << " | 데이터 수(n*n) : " << n * n << "개 | n * n 배열 초기화 완료됨" << endl;
    cout << "--------------------------------" << endl << endl;
    // 3. 1~100,000 사이의 랜덤값 k를 선택하고, k번째 작은 수를 찾으시오.
    int k = RandomNumber(1, 100000);
    // 파이썬처럼 2차원에서 1차원으로 변환
    int kRow = k / cols;
    int kCol = k % cols;

    // +a) 위 과정을 "정렬 후 k번째 작은값 찾는 방법", "MIN값부터 차례로 k번째까지 반복하여 찾는 방법"과 비교하여 
    //     어떤 방식이 더 효율적인지 실험적으로 보이시오.

    int comparisonCount = 0, comparisonCount2 = 0;
    ThreePartQuickSort(arr, cols, 0, 0, rows - 1, cols - 1, &comparisonCount);
    //Selection(arr2, cols, 0, 0, rows - 1, cols - 1, &comparisonCount2);

    // 결과 출력
    cout << "정렬 후 k번째 작은값 찾는 방법 결과" << endl;
    cout << "k : " << arr[kRow][kCol] << " " << endl;
    cout << "전체 비교 횟수: " << comparisonCount << endl;
    cout << "--------------------------------" << endl << endl;
    /*
    cout << "MIN값부터 차례로 k번째까지 반복하여 찾는 방법" << endl;
    cout << "k : " << arr[kRow][kCol] << " " << endl;
    cout << "전체 비교 횟수: " << comparisonCount2 << endl;
    cout << "--------------------------------" << endl;

    cout << endl << endl;
    cout << "[결론]" << endl;
    if(comparisonCount < comparisonCount2)
        cout << "정렬 후 k번째 작은값 찾는 방법이 더 효율적입니다." << endl;
    else
        cout << "MIN값부터 차례로 k번째까지 반복하여 찾는 방법이 더 효율적입니다." << endl;
        */
    return 0;
}
