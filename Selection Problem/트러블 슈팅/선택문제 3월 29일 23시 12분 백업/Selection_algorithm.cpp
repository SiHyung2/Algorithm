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

// ���� �Լ� (2���� �迭)
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

    // ���� ����
    if (left > startIdx) {
        int leftRow = (left - 1) / colMaxIndex;
        int leftCol = (left - 1) % colMaxIndex;
        ThreePartQuickSort(arr_2d, colMaxIndex, startRow, startCol, leftRow, leftCol, p_comparisonCount);
    }

    // ������ ����
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



    //���� ���� �˰��� �ۼ��ϰ�.. ��Ƚ���� ����ؾ���.
}

*/
int main() {

    // 1. 500~1,000 ������ �Է°� n�� �����ÿ�.
    int n = RandomNumber(500, 1000);

    // 2. n x n ũ���� ������ �迭�� ����� 1~100,000 ������ ���������� ä��ÿ�.
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
            
            ���⼭ �̻��ϰ� ������ ��!! ��... arr2[i][j] = 1;
        }
    }
    cout << "n: " << n << " | ������ ��(n*n) : " << n * n << "�� | n * n �迭 �ʱ�ȭ �Ϸ��" << endl;
    cout << "--------------------------------" << endl << endl;
    // 3. 1~100,000 ������ ������ k�� �����ϰ�, k��° ���� ���� ã���ÿ�.
    int k = RandomNumber(1, 100000);
    // ���̽�ó�� 2�������� 1�������� ��ȯ
    int kRow = k / cols;
    int kCol = k % cols;

    // +a) �� ������ "���� �� k��° ������ ã�� ���", "MIN������ ���ʷ� k��°���� �ݺ��Ͽ� ã�� ���"�� ���Ͽ� 
    //     � ����� �� ȿ�������� ���������� ���̽ÿ�.

    int comparisonCount = 0, comparisonCount2 = 0;
    ThreePartQuickSort(arr, cols, 0, 0, rows - 1, cols - 1, &comparisonCount);
    //Selection(arr2, cols, 0, 0, rows - 1, cols - 1, &comparisonCount2);

    // ��� ���
    cout << "���� �� k��° ������ ã�� ��� ���" << endl;
    cout << "k : " << arr[kRow][kCol] << " " << endl;
    cout << "��ü �� Ƚ��: " << comparisonCount << endl;
    cout << "--------------------------------" << endl << endl;
    /*
    cout << "MIN������ ���ʷ� k��°���� �ݺ��Ͽ� ã�� ���" << endl;
    cout << "k : " << arr[kRow][kCol] << " " << endl;
    cout << "��ü �� Ƚ��: " << comparisonCount2 << endl;
    cout << "--------------------------------" << endl;

    cout << endl << endl;
    cout << "[���]" << endl;
    if(comparisonCount < comparisonCount2)
        cout << "���� �� k��° ������ ã�� ����� �� ȿ�����Դϴ�." << endl;
    else
        cout << "MIN������ ���ʷ� k��°���� �ݺ��Ͽ� ã�� ����� �� ȿ�����Դϴ�." << endl;
        */
    return 0;
}
