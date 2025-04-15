#include "CodeForces.h"
#include "FastVersionedMap.h"

void FastVersionedMap_test()
{
    // Create a FastVersionedMap without zeroing out arrays (for speed)
    FastVersionedMap mapFast(false);

    // (Optionally) reset the map to set a clean currentVersion.
    mapFast.reset();

    // Use the map
    mapFast[5] = 42;  // Marks key 5 as valid for currentVersion, with value 42

    if (mapFast.contains(5)) {
        std::cout << "Key 5 exists with value: " << mapFast[5] << '\n';
    }

    // Remove key 5
    mapFast.remove(5);

    // Alternatively, create a map with preinitialization if you want guaranteed clean state:
    FastVersionedMap mapWithInit(true);
    // Now mapWithInit.keyVersion and mapWithInit.keyValue are guaranteed to be zeroed.
}

int main() {
    cout << "Test FastVersionedMap data structure: " << endl;
    FastVersionedMap_test();

    cout << "Starting CodeForces tests:" << endl;

    return 0;
}