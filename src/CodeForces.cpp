#include "CodeForces.h"
#include "FastVersionedMap.h"
#include "LargestSubmatrix3_407D.h"

struct LargestSubmatrix3TestCase {
    string input;
    int expectedResult;
    LargestSubmatrix3TestCase(const string& in, int exp)
        : input(in), expectedResult(exp) {}
};

void FastVersionedMap_test()
{
    // Because this is a stack‑allocated map, we MUST zero‑initialize its internal arrays
    // to avoid garbage versions. reset() only increments currentVersion—it does NOT clear keyVersion!
    FastVersionedMap mapFast(true);

    // (Optionally) reset the map to set a clean currentVersion.
    mapFast.reset();

    // Use the map
    mapFast[5] = 42;  // Marks key 5 as valid for currentVersion, with value 42

    if (mapFast.contains(5)) {
        std::cout << "Key 5 exists with value: " << mapFast[5] << '\n';
    }

    // Remove key 5
    mapFast.remove(5);
}

static void runLargestSubmatrix3_407D_tests() {
    vector<LargestSubmatrix3TestCase> testCases = {
        LargestSubmatrix3TestCase(
            "3 3\n"
            "1 3 1\n"
            "4 5 6\n"
            "2 6 1\n",
            6
        ),
        LargestSubmatrix3TestCase(
            "3 4\n"
            "5 2 3 1\n"
            "3 3 5 3\n"
            "4 4 4 5\n",
            4
        ),
        LargestSubmatrix3TestCase(
            "2 6\n"
            "1 2 3 4 5 6\n"
            "8 6 7 8 9 1\n",
            8
        )
    };

    for (size_t i = 0; i < testCases.size(); ++i) {
        // Redirect cin to read from the test-case string
        istringstream in(testCases[i].input);
        auto* oldBuf = cin.rdbuf(in.rdbuf());

        int result = largestSubmatrix3();

        // Restore original cin buffer
        cin.rdbuf(oldBuf);

        cout << "LargestSubmatrix3_407D Test " << (i + 1)
             << ": res = " << (result == testCases[i].expectedResult ? "PASS" : "FAIL")
             << " (Expected: " << testCases[i].expectedResult
             << ", Got: " << result << ")" << endl;
    }
}

int main() {
    cout << "Test FastVersionedMap data structure: " << endl;
    FastVersionedMap_test();

    cout << "Starting CodeForces tests:" << endl;
    runLargestSubmatrix3_407D_tests();

    return 0;
}