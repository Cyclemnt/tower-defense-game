#ifndef IMAP_SOURCE_HPP
#define IMAP_SOURCE_HPP

#include <string>
#include <memory>

class Map;
class Cores;

/**
 * @brief Interface for different map sources (file, procedural).
 */
class IMapSource {
public:
    virtual ~IMapSource() = default;
    virtual void buildMap(Map& map, Cores* cores) = 0;
};

#endif // IMAP_SOURCE_HPP
