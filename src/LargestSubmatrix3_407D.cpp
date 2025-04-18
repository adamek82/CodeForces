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

// Simple rectangle struct: stores top-left (r1,c1) and bottom-right (r2,c2)
struct Rect {
    int r1, c1, r2, c2;
};

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

    // ----------------------------------------------------------------
    // Step 3: Propagate to all row ranges and compute max area (O(n^2 * m))
    //
    // We now have dp filled for:
    //  - dp[r][r][c]      (single rows)
    //  - dp[r1][r2][c]    (exactly two rows)
    //
    // For any r1 < r2 and start c, dp[r1][r2][c] can be refined by:
    //   min of:
    //     (1) dp[r1+1][r2][c]   – drop top row
    //     (2) dp[r1][r2-1][c]   – drop bottom row
    //     (3) dp[r1][r2][c+1]   – advance start column
    //
    // Case (4) where both top and bottom drops happen together is
    // already captured by Step 2 preprocessing.
    //
    // We iterate:
    //   for r1 = n..1
    //     for r2 = r1..n
    //       for c = m..1
    //         take min over valid neighbors (check boundaries)
    //         compute area = (r2 - r1 + 1) * (dp[r1][r2][c] - c + 1)
    //         update max_area
    // ----------------------------------------------------------------
    int max_area = 0;
    Rect bestRect{1, 1, 1, 1};

    for (int r1 = n; r1 >= 1; --r1) {
        for (int r2 = r1; r2 <= n; ++r2) {
            for (int c = m; c >= 1; --c) {
                int best = dp[r1][r2][c];
                // (1) drop top row
                if (r1 < r2)
                    best = min(best, dp[r1 + 1][r2][c]);
                // (2) drop bottom row
                if (r1 < r2)
                    best = min(best, dp[r1][r2 - 1][c]);
                // (3) advance start column
                if (c < m)
                    best = min(best, dp[r1][r2][c + 1]);

                dp[r1][r2][c] = best;

                // compute area for submatrix [r1..r2]×[c..best]
                int width = best - c + 1;
                if (width > 0) {
                    int height = r2 - r1 + 1;
                    max_area = max(max_area, width * height);
                    bestRect = { r1, c, r2, best };
                }
            }
        }
    }

    // Print the coordinates of the best rectangle
    cout << bestRect.r1 << ' '
         << bestRect.c1 << ' '
         << bestRect.r2 << ' '
         << bestRect.c2 << '\n';

    return max_area;
}