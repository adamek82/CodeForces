#include <cstring>  // For memset

// Define the grid size, such that keys range in [0, N*N)
// Tweak this value as needed. Here, N is set to 401, which means there are 401*401 possible keys.
const int N = 401;

/**
 * FastVersionedMap is a specialized mapping container designed for scenarios where:
 *  - Keys are integers within a known, contiguous range [0, MAX_KEYS).
 *  - Fast "reset" or "clear" operations are essential (e.g., in competitive programming challenges).
 *
 * How It Works:
 *  - The map uses a versioning strategy. Each key is associated with a 'version' in the keyVersion array.
 *  - The current valid version is tracked by the currentVersion variable.
 *  - When a key is accessed via operator[], its version is updated to currentVersion, which effectively marks it as valid.
 *  - Clearing the map is performed in O(1) time by simply incrementing currentVersion, thus invalidating all previously set keys.
 *
 * Key Methods (short summary):
 *  - reset(): Increments currentVersion to logically clear the map.
 *  - operator[](int k): Provides O(1) access to the value associated with key 'k' and marks it as valid.
 *  - contains(int k): Checks if key 'k' is valid in the current version.
 *  - remove(int k): Invalidates key 'k' by resetting its version.
 *
 * Note on Initialization:
 *  - Global (static) instances are zero-initialized by the compiler, so uninitialized arrays will start at 0.
 *  - Local (automatic) instances are not zero-initialized by default; use the preInitialize parameter in the constructor
 *    (or value-initialize the object) if a clean state is required.
 */
class FastVersionedMap {
private:
    // Maximum number of keys expected (keys in the range [0, N*N)).
    // Adjust this value if you need a different range.
    static const int MAX_KEYS = N * N;

    // Tracks the current version (or iteration) for valid keys.
    // Incrementing this effectively "clears" the map.
    int currentVersion;

    // Array that stores, for each key, the version when it was last updated.
    int keyVersion[MAX_KEYS];

    // Array that stores the value associated with each key.
    int keyValue[MAX_KEYS];

public:
    /**
     * Constructor for FastVersionedMap.
     *
     * @param preInitialize If true, zero-initializes the keyVersion and keyValue arrays using memset.
     *                      Useful for ensuring a clean state when working with local (automatic) instances.
     *                      Defaults to false.
     *
     * Note: For global instances, the arrays are already zero-initialized.
     */
    FastVersionedMap(bool preInitialize = false)
        : currentVersion(0)
    {
        if (preInitialize) {
            std::memset(keyVersion, 0, sizeof(keyVersion));
            std::memset(keyValue, 0, sizeof(keyValue));
        }
    }

    /**
     * Increments currentVersion, effectively "clearing" the map.
     * All keys set in previous versions become invalid.
     */
    void reset() {
        ++currentVersion;
    }

    /**
     * Access operator for key 'k'. Marks key 'k' as valid in the current version,
     * and returns a reference to its associated value.
     *
     * @param k The key (should be in the range [0, MAX_KEYS)).
     * @return Reference to the value associated with key 'k'.
     */
    int& operator[](int k) {
        keyVersion[k] = currentVersion;
        return keyValue[k];
    }

    /**
     * Checks if key 'k' is valid in the current version of the map.
     *
     * @param k The key to check.
     * @return true if key 'k' is valid; false otherwise.
     */
    bool contains(int k) const {
        return keyVersion[k] == currentVersion;
    }

    /**
     * Invalidates key 'k' by resetting its associated version.
     *
     * @param k The key to remove.
     */
    void remove(int k) {
        keyVersion[k] = 0;
    }
};
