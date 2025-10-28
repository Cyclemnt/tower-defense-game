#ifndef IMAP_SOURCE_HPP
#define IMAP_SOURCE_HPP

#include <memory>

class Map;
class Cores;

/**
 * @interface IMapSource
 * @brief Abstract interface defining how a Map is built.
 *
 * Different map sources (text file, JSON, procedural generation, etc.)
 * must implement this interface so they can be plugged into the Map
 * constructor seamlessly.
 */
class IMapSource {
public:
    virtual ~IMapSource() = default;

    /// @brief Populates the given Map instance using this source.
    /// @param map The map object to fill with tiles.
    /// @param cores Pointer to the Cores manager (for CoreStorage linkage).
    virtual void buildMap(Map& map, Cores* cores) = 0;
};

#endif // IMAP_SOURCE_HPP
