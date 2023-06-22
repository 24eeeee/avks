#include <iostream>
#include <time.h>
#include <omp.h>

using namespace std;

int main() {
    srand(time(nullptr));
    int n = rand() % 7 + 1, m = rand() % 7 + 1, l = rand() % 7 + 1;
    int ** A = new int * [n];
    int ** B = new int * [m];
    for (int i = 0; i < n; ++i) {A[i] = new int [m];}
    for (int i = 0; i < m; ++i) {B[i] = new int [l];}
#pragma omp task
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {A[i][j] = rand() % 11 + 1;}
    }
#pragma omp task
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < l; ++j) {B[i][j] = rand() % 11 + 1;}
    }
#pragma omp taskwait
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {cout << A[i][j] << '\t';}
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < l; ++j) {cout << B[i][j] << '\t';}
        cout << endl;
    }
    cout << endl;

    int ** C = new int * [n];
    for (int i = 0; i < n; ++i) {C[i] = new int [l];}

    int sum = 0;
#pragma omp parallel for shared(A, B, C) private (i, j, k)
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < l; ++j) {
            for (int k = 0; k < m; ++k) {sum += A[i][k] * B[k][j];}
            C[i][j] = sum;
            sum = 0;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < l; ++j) {cout << C[i][j] << '\t';}
        cout << endl;
    }
}

