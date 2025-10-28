#ifndef TXT_MAP_SOURCE_HPP
#define TXT_MAP_SOURCE_HPP

#include <string>
#include "iMapSource.hpp"

/**
 * @class TxtMapSource
 * @brief Loads a map from a text file (.txt) representation.
 *
 * Each character in the text file defines a tile:
 * ```
 * # - Path
 * O - Open zone (buildable)
 * E - Entry zone
 * X - Exit zone
 * C - Core storage
 * . - Empty zone (default)
 * ```
 *
 * Whitespace is ignored. All rows must have the same width.
 */
class TxtMapSource final : public IMapSource {
private:
    std::string filename; ///< Path to the text file.

public:
    /// @brief Constructs a TxtMapSource from a file path.
    /// @param path Path to the .txt map file.
    explicit TxtMapSource(std::string path);

    /// @brief Builds the map using the .txt file layout.
    /// @param map The target map to populate.
    /// @param cores Pointer to the Cores object (may be null).
    void buildMap(Map& map, Cores* cores) override;
};

#endif // TXT_MAP_SOURCE_HPP
