#include <iostream>
#include <omp.h>

using namespace std;

int main() {
    int n = 100000000;
    long double pi = 0;
#pragma omp parallel for reduction(+:pi)
    for (int i = 0; i < n; i += 1) {
        long double xi = (0.5 + i) / n;
        pi += 4.0 / (1.0 + xi * xi);
    }
    cout.precision(9);
    cout << pi/n << endl;
}


