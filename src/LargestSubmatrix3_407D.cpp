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
    // Runs in O(m) time per row, so overall Step 1 is O(n * m).
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

    // ----------------------------------------------------------------
    // Step 2: Two-row initialization.
    //
    // For each pair of rows (r1 < r2) and each start column c,
    // we want dp[r1][r2][c] = the maximum C ≥ c such that all entries
    // in rows r1 and r2 across columns [c..C] are distinct.
    //
    // We again sweep right-to-left for each (r1, r2):
    //  - reset lastPosMap once per row pair (O(1))
    //  - maintain 'limit' = current furthest valid end column
    //  - at each column c:
    //      1. check v1 = a[r1][c]; if seen, limit = min(limit, lastPosMap[v1]-1)
    //      2. update lastPosMap[v1] = c
    //      3. check v2 = a[r2][c]; if seen, limit = min(limit, lastPosMap[v2]-1)
    //      4. update lastPosMap[v2] = c
    //      5. set dp[r1][r2][c] = limit
    //
    // Each sweep is O(m), and there are O(n^2) row-pairs, so
    // Step 2 runs in O(n^2 * m) time overall.
    // ----------------------------------------------------------------
    for (int r1 = 1; r1 <= n; ++r1) {
        for (int r2 = r1 + 1; r2 <= n; ++r2) {
            lastPosMap.reset();
            int limit = m;
            for (int c = m; c >= 1; --c) {
                // process row r1's value
                int v1 = a[r1][c];
                if (lastPosMap.contains(v1))
                    limit = min(limit, lastPosMap[v1] - 1);
                lastPosMap[v1] = c;

                // process row r2's value
                int v2 = a[r2][c];
                if (lastPosMap.contains(v2))
                    limit = min(limit, lastPosMap[v2] - 1);
                lastPosMap[v2] = c;

                dp[r1][r2][c] = limit;
            }
        }
    }

    // TODO: Steps 3+ to extend dp to larger row ranges and compute max area.

    return 0;
}