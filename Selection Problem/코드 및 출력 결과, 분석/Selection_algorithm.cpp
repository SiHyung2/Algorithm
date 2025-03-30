#include <iostream>
#include <random>
#include <limits.h> // INT_MAX

using namespace std;


int RandomNumber(int start, int end) {
    random_device rd;
    mt19937_64 rng(rd());

    uniform_int_distribution<__int64> dist(start, end);
    int number = dist(rng);

    return number;
}


void SwapArray(int* arr, int index1ToChange, int index2ToChange) {
    int temp = arr[index1ToChange];
    arr[index1ToChange] = arr[index2ToChange];
    arr[index2ToChange] = temp;
}


int Selection(int* arr, int left, int right, int k, int* p_comparisonCount)
{
    if (left == right)
        return arr[left];

    int pivot = (left + right) / 2;
    SwapArray(arr, pivot, left);

    int low = left + 1;
    int high = right;

    while (low <= high) {
        while (low <= right && arr[low] <= arr[left]) {
            *p_comparisonCount += 1;
            low++;
        }
        while (high >= left && arr[high] > arr[left]) {
            *p_comparisonCount += 1;
            high--;
        }

        if (low < high) {
            SwapArray(arr, low, high);
            low++;
            high--;
        }
    }

    SwapArray(arr, left, low - 1);

    int pivotRank = low - left;



    if (k == pivotRank)
        return arr[low - 1];
    else if (k < pivotRank)
        return Selection(arr, left, low - 2, k, p_comparisonCount);
    else
        return Selection(arr, low, right, k - pivotRank, p_comparisonCount);
}




void MedianQuickSort(int* arr, int start, int end, int* p_comparisonCount) {
    if (start >= end) return;

    int pivotIndex = (start + end) / 2;
    int pivotVal = arr[pivotIndex];

    int left = start;
    int i = start;
    int right = end;

    while (i <= right) {
        (*p_comparisonCount)++;

        if (arr[i] < pivotVal) {
            SwapArray(arr, left, i);
            left++;
            i++;
        }
        else if (arr[i] > pivotVal) {
            SwapArray(arr, i, right);
            right--;
        }
        else {
            i++;
        }
    }

    MedianQuickSort(arr, start, left - 1, p_comparisonCount);
    MedianQuickSort(arr, right + 1, end, p_comparisonCount);
}


/*
// 리펙토링 후.. 작동을 안해서 포기함
void ThreePartQuickSort(int* arr, int start, int end, int* p_comparisonCount) {
    if (start >= end) return;
    cout << "[진입] start: " << start << ", end: " << end << ", size: " << (end - start + 1) << endl;

    int pivot = (start + end) / 2;
    int left = start;
    int right = end;
    int pivotVal = arr[pivot];
    int leftVal = arr[left];
    int rightVal = arr[right];

    while (left <= right) {
        leftVal = arr[left];
        rightVal = arr[right];

        while (leftVal <= pivotVal) {
            (*p_comparisonCount)++;
            leftVal = arr[left];
            left++;
        }

        while (rightVal >= pivotVal && right > start) {
            (*p_comparisonCount)++;
            rightVal = arr[right];
            right--;
        }

        if (left > right)
            SwapArray(arr, right, pivot);
        else
            SwapArray(arr, right, left);

        if (*p_comparisonCount % 100000 == 0) {
            cout << "[디버그] 반복 중... left = " << left << ", right = " << right << endl;
        }

    }
    ThreePartQuickSort(arr, start, right - 1, p_comparisonCount);
    ThreePartQuickSort(arr, right + 1, end, p_comparisonCount);
}
*/

int FindMinimum_k_times(int* arr, int length, int k, long long* p_comparisonCount3) {

    int* visited = new int[length]();

    int result = -1;

    for (int step = 0; step < k; step++) {
        int minVal = INT_MAX;
        int minIndex = -1;

        for (int i = 0; i < length; i++) {
            *p_comparisonCount3 += 1;
            if (!visited[i] && arr[i] < minVal) {
                minVal = arr[i];
                minIndex = i;
            }
        }

        if (minIndex != -1) {
            visited[minIndex] = 1;
            result = minVal;
        }
        else {
            break;
        }
    }

    delete[] visited;
    return result;
}



int main() {

    // 1. 500~1,000 사이의 입력값 n을 받으시오.
    int n = RandomNumber(500, 1000);

    // 2. n x n 크기의 이차원 배열을 만들고 1~100,000 사이의 랜덤값으로 채우시오.
    int rows = n, cols = n;
    int** arr_2d = new int* [rows];
    int** arr2_2d = new int* [rows];
    int** arr3_2d = new int* [rows];
    int randomData = 0;
    int temp = 0;
    for (int i = 0; i < rows; ++i) {
        arr_2d[i] = new int[cols];
        arr2_2d[i] = new int[cols];
        arr3_2d[i] = new int[cols];
        for (int j = 0; j < cols; ++j) {
            randomData = RandomNumber(1, 100000);
            arr_2d[i][j] = randomData;
            arr2_2d[i][j] = randomData;
            arr3_2d[i][j] = randomData;
        }
    }
    cout << "n : " << n << " | 데이터 수(n*n) : " << n * n << "개 | n * n 배열 3개 초기화 완료됨" << endl;

    
    int arr_length = cols * rows;
    int arr2_length = cols * rows;
    int arr3_length = cols * rows;

    int* arr = new int[arr_length]();
    int* arr2 = new int[arr2_length]();
    int* arr3 = new int[arr3_length]();

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int index = (i * cols) + j;
            arr[index] = arr_2d[i][j];
            arr2[index] = arr2_2d[i][j];
            arr3[index] = arr3_2d[i][j];
        }
    }

    cout << "2차원 배열을 1차원 배열로 변환완료했습니다" << endl;

    // 3. 1~100,000 사이의 랜덤값 k를 선택하고, k번째 작은 수를 찾으시오.
    int k = RandomNumber(1, 100000);

    int kIndex = k - 1;
    cout << "k : " << k << endl;
    int kRow = kIndex / cols;
    int kCol = kIndex % cols;
    cout << "--------------------------------" << endl;
    cout << "비교 횟수를 셀때, 조건문은 제외하였음" << endl;
    cout << "--------------------------------" << endl << endl;

    // +a) 위 과정을 "정렬 후 k번째 작은값 찾는 방법", "MIN값부터 차례로 k번째까지 반복하여 찾는 방법"과 비교하여 
    //     어떤 방식이 더 효율적인지 실험적으로 보이시오.

    int comparisonCount = 0, comparisonCount2 = 0;
    long long comparisonCount3 = 0;
    
    MedianQuickSort(arr2, 0, arr2_length -1, &comparisonCount2);
    // ThreePartQuickSort(arr, 0, arr2_length - 1, &comparisonCount2);

    int kth_smallest_value, kth_smallest_value2, kth_smallest_value3;


    // 결과 출력
    kth_smallest_value = Selection(arr, 0, arr_length - 1, k, &comparisonCount);
    cout << "선택 문제 결과 : Selection Problem" << endl;
    cout << "k번째 작은값 : " << kth_smallest_value << endl;
    cout << "비교 횟수: " << comparisonCount << endl;
    cout << "--------------------------------" << endl << endl;

    kth_smallest_value2 = arr2[k - 1];
    cout << "정렬 후 k번째 작은값 찾는 방법 결과 : MedianQuickSort 정렬 후 Search" << endl;
    cout << "k번째 작은값 " << "arr2[" << kRow << "][" << kCol << "] : " << kth_smallest_value2 << " " << endl;
    cout << "비교 횟수: " << comparisonCount2 << endl;
    cout << "--------------------------------" << endl << endl;
    
    cout << "MIN값부터 차례로 k번째까지 반복하여 찾는 방법" << endl;
    kth_smallest_value3 = FindMinimum_k_times(arr3, arr3_length, k, &comparisonCount3);
    cout << "k번째 작은값 : " << kth_smallest_value3 << endl;
    cout << "비교 횟수: " << comparisonCount3 << endl;
    cout << "--------------------------------" << endl;

    cout << endl << endl;


    // 정렬 후 정렬 확인
    for (int i = 1; i < arr2_length; i++) {
        if (arr2[i - 1] > arr2[i]) {
            cout << "정렬 안 됨: arr2[" << i - 1 << "] = " << arr2[i - 1]
                << ", arr2[" << i << "] = " << arr2[i] << endl;
            break;
        }
    }


    cout << "[결론]" << endl;
    if(comparisonCount < comparisonCount2 && comparisonCount < comparisonCount3)
        cout << "선택 문제 방법이 더 효율적입니다." << endl;
    else if (comparisonCount2 < comparisonCount && comparisonCount2 < comparisonCount3)
        cout << "정렬 후 k번째 작은값 찾는 방법이 더 효율적입니다." << endl;
    else if (comparisonCount3 < comparisonCount && comparisonCount3 < comparisonCount2)
        cout << "MIN값부터 차례로 k번째까지 반복하여 찾는 방법이 더 효율적입니다." << endl;
	else
		cout << "같은 비교횟수가 있거나 비교할 수 없습니다." << endl;
    return 0;




}
