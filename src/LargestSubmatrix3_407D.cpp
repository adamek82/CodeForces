#include "LargestSubmatrix3_407D.h"
#include <iostream>

using namespace std;

const int MAX_N = 400;  // maximum number of rows
const int MAX_M = 400;  // maximum number of columns

static int n, m;
static int a[MAX_N + 1][MAX_M + 1];  // using 1-based indexing: [1..n][1..m]

int largestSubmatrix3() {
    // Read dimensions
    cin >> n >> m;

    // Read matrix entries with 1-based loops
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }

    // TODO: implement the algorithm to compute and return the maximum area
    return 0;
}