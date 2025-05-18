#include <iostream>
#include <cstdlib>
#include <ctime>   
#include <vector>
#include <fstream> 
#define int_max 1000000000

using namespace std;


// 행렬 곱셈 최소 연산 횟수 구하기
int matrix_chain_order(int* d, int n) {
    int** C = new int* [n + 1];
    int** S = new int* [n + 1];  

    for (int i = 0; i <= n; i++) {
        C[i] = new int[n + 1];
        S[i] = new int[n + 1];
        for (int j = 0; j <= n; j++) {
            if (i == j)
                C[i][j] = 0;
            else
                C[i][j] = int_max;
            S[i][j] = 0;
        }
    }

    int temp = 0;
    
    for (int L = 1; L <= n - 1; L++) {
        for (int i = 1; i <= n - L; i++) {
            int j = i + L;
            for (int k = i; k < j; k++) {
                temp = C[i][k] + C[k + 1][j] + d[i - 1] * d[k] * d[j];
                if (temp < C[i][j]) {
                    C[i][j] = temp;
                    S[i][j] = k; 
                }
            }
        }
    }

    int result = C[1][n];

    
    for (int i = 0; i <= n; i++) {
        delete[] C[i];
        delete[] S[i];
    }
    delete[] C;
    delete[] S;

    return result;
}

int main(void) {
    srand(time(0));
    int n_array[6] = { 5, 6, 7, 8, 9, 10 };
    vector<int> operations; 


    for (int n : n_array) {
        int* d = new int[n + 1];

        
        for (int i = 0; i <= n; i++) {
            d[i] = rand() % 20 + 1;
        }


        int min_operations = matrix_chain_order(d, n);


        operations.push_back(min_operations);

        delete[] d;
    }

    
    cout << "Matrix size vs. Operations\n==========================\n";
    cout << "Matrix Count\tOperations\n";
    for (auto i = 0; i < 6; i++) {
        cout << n_array[i] << "\t\t" << operations[i] << endl;
    }

    // 결과를 CSV 파일로 저장
    ofstream file("matrix_operations.csv");
    file << "Matrix Count,Operations\n";
    for (auto i = 0; i < 6; i++) { 
        file << n_array[i] << "," << operations[i] << endl;
    }
    file.close();

    return 0;
}
