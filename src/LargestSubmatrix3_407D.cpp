#include "LargestSubmatrix3_407D.h"
#include "FastVersionedMap.h"
#include <iostream>

using namespace std;

const int MAX_N = 400;  // maximum number of rows
const int MAX_M = 400;  // maximum number of columns

static int n, m;
static int a[MAX_N + 1][MAX_M + 1];              // matrix entries, 1-based: [1..n][1..m]
static int dp[MAX_N + 1][MAX_N + 1][MAX_M + 1];  // dp[i1][i2][cStart] = furthest valid column

// Global versioned map: maps a value to its last-seen column index in the current pass.
// As a global (static storage), its arrays are zero-initialized automatically.
static FastVersionedMap lastPosMap;

int largestSubmatrix3() {
    // Read dimensions
    cin >> n >> m;

    // Read matrix entries with 1-based loops
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }

    // ----------------------------------------------------------------
    // Step 1: Initialize dp for single-row submatrices.
    //
    // For each row r and each starting column c, we need:
    //   dp[r][r][c] = the maximum column C ≥ c
    //                 such that all elements a[r][c..C] are distinct.
    //
    // We perform a right-to-left sweep:
    //   - Call lastPosMap.reset() once per row in O(1).
    //   - Maintain a running 'limit' = the furthest valid right boundary.
    //   - At each column c (from m down to 1):
    //       • If value v = a[r][c] was seen to the right, tighten
    //         limit = min(limit, lastPosMap[v] - 1).
    //       • Set dp[r][r][c] = limit.
    //       • Record lastPosMap[v] = c.
    //
    // This runs in O(m) time per row, with no inner while-loops.
    // ----------------------------------------------------------------
    for (int r = 1; r <= n; ++r) {
        lastPosMap.reset();         // clear the map in O(1)
        int limit = m;              // the furthest valid right boundary

        // sweep from right to left
        for (int c = m; c >= 1; --c) {
            int v = a[r][c];
            if (lastPosMap.contains(v)) {
                // v re‑appears at lastPosMap[v], so we can’t go past that – 1
                limit = min(limit, lastPosMap[v] - 1);
            }
            dp[r][r][c] = limit;
            lastPosMap[v] = c;      // record that v was last seen here
        }
    }

    // TODO: Steps 2+ to extend dp to multi-row ranges and compute maximum area.
    return 0;
}