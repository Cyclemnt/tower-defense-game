#ifndef I_MAP_SOURCE_HPP
#define I_MAP_SOURCE_HPP

#include <string>
#include <vector>
namespace tdg::core { struct Tile; } // Forward declaration

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

        /// Load a map by id or path. Throw std::runtime_error on failure.
        virtual MapData loadMap(unsigned int level) const = 0;
    };

} // namespace tdg::core

#endif // I_MAP_SOURCE_HPP
