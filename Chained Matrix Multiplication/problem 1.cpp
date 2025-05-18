#include <iostream>
#define int_max 1000000000

using namespace std;

// 최적의 괄호 묶기 순서를 출력하는 함수
void print_optimal_parens(int** S, int i, int j) {
    if (i == j) {
        cout << "A" << i;  
    }
    else {
        cout << "(";
        print_optimal_parens(S, i, S[i][j]);  // 왼쪽 분할
        cout << " * "; 
        print_optimal_parens(S, S[i][j] + 1, j);  // 오른쪽 분할
        cout << ")";
    }
}

int main(void)
{
    int n = 4;
    // cin >> N;
    int* d = new int[n + 1];
    int** C = new int* [n + 1];
    int** S = new int* [n + 1]; 
    for (int i = 0; i < n + 1; i++) {
        C[i] = new int[n + 1];
        S[i] = new int[n + 1];
        for (int j = 0; j < n + 1; j++) {
            if (i == j)
                C[i][j] = 0;
            else
                C[i][j] = int_max;
            S[i][j] = 0;
        }
    }
    int* mul_sum = new int[n];
    int final_solution;
    int temp = 0;

    d[0] = 10;
    d[1] = 20;
    d[2] = 5;
    d[3] = 15;
    d[4] = 30;

    
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

    
    cout << "Chained Matrix Multiplication\n===================================\n";
    cout << "M\t1\t2\t3\t4\n";
    for (int i = 1; i <= n; i++) {
        cout << i << "\t";
        for (int j = 1; j <= n; j++) {
            if (C[i][j] == int_max) cout << "0\t";
            else cout << C[i][j] << "\t";
        }
        cout << endl;
    }

    final_solution = C[1][n];
    cout << "Final Solution : " << final_solution << endl << endl;

    cout << "Implicit Order for Matrix Multiplication : ";
    print_optimal_parens(S, 1, n);
    cout << endl;

    for (int i = 0; i <= n; i++) {
        delete[] C[i];
        delete[] S[i];
    }
    delete[] C;
    delete[] S;
    delete[] d;

    return 0;
}
