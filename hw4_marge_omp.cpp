#include <cstring>
#include <ctime>
#include <iostream>
#include <omp.h>

using namespace std;

void merge(int * data, int n, int * tmp) {
    int i = 0;
    int mid = n / 2;
    int ti = 0;
    while (i < n/2 && mid < n) {
        if (data[i] < data[mid]) {
            tmp[ti] = data[i];
            ++ti;
            ++i;
        } else {
            tmp[ti] = data[mid];
            ++ti;
            ++mid;
        }
    }
    while (i < n/2) {
        tmp[ti] = data[i];
        ++ti;
        ++i;
    }
    while (mid < n) {
        tmp[ti] = data[mid];
        ++ti;
        ++mid;
    }
    memcpy(data, tmp, n * sizeof(int));

}

void mergesort(int * data, int n, int * tmp) {
    if (n < 2) return;
#pragma omp task private (data, n, tmp)
    mergesort(data, n / 2, tmp);
#pragma omp task private (data, n, tmp)
    mergesort(data + (n / 2), n - (n / 2), tmp);
#pragma omp taskwait
    merge(data, n, tmp);
}

void print(int * x, int n) {
    for (int i = 0; i < n; ++i) {
        cout << x[i] << ' ';
    }
    cout << endl;
}

int main() {
    srand(time(nullptr));
    int n = rand() % 21 + 10;
    int * data = new int [n];
    for (int i = 0; i < n; ++i) {
        data[i] = rand() % 21;
    }
    int * tmp = new int [n];
    print(data, n);
    mergesort(data, n, tmp);
    print(data, n);
}

