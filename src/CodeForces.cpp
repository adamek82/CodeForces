#include "CodeForces.h"
#include "FastVersionedMap.h"

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

int main() {
    cout << "Test FastVersionedMap data structure: " << endl;
    FastVersionedMap_test();

    cout << "Starting CodeForces tests:" << endl;

    return 0;
}