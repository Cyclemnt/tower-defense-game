#ifndef I_MAP_SOURCE_HPP
#define I_MAP_SOURCE_HPP

#include <vector>

namespace tdg::core { struct Tile; }

namespace tdg::core {

    struct MapData {
        int width{0};
        int height{0};
        std::vector<Tile> tiles;
    };
    
    /// @brief Interface for map sources (files, editor, network).
    /// Domain depends on this to obtain a MapData; implementations live in infra.
    class IMapSource {
    public:
        virtual ~IMapSource() = default;

        virtual void setLevel(unsigned int level) = 0; // Sets the level of the map
        virtual MapData loadMap() const = 0; // Loads the description of a map
    };

} // namespace tdg::core

#endif // I_MAP_SOURCE_HPP
