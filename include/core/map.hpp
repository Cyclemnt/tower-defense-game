#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <memory>
#include <string>
#include <functional>
#include "core/tile.hpp"

namespace tdg::core { class IMapSource; class IVideoRenderer; }

namespace tdg::core {

    /// @brief Map stores tile layout and provides queries.
    class Map {
    public:
        explicit Map(std::shared_ptr<IMapSource> source);

        int width() const noexcept { return m_width; }
        int height() const noexcept { return m_height; }

        const Tile* tileAt(int x, int y) const noexcept; // Returns a const ptr to the (x,y) tile
        Tile* tileAt(int x, int y) noexcept; // Returns a ptr to the (x,y) tile

        std::vector<const Tile*> neighbors(const Tile* tile) const; // Provides neighbors of a tile (used by pathfinders)

        std::vector<Tile*> entryPoints() const noexcept { return m_entryPoints; }
        std::vector<Tile*> exitPoints() const noexcept { return m_exitPoints; }
        Tile* corePoint() const noexcept { return m_corePoint; }

        bool canRecieveTowerAt(int x, int y) const noexcept; // Says if a tile can recieve a tower
        bool hasTowerAt(int x, int y) const noexcept; // Says if a tile has a tower
        bool markTowerAt(int x, int y) noexcept; // Marks tower presence on a tile
        bool removeTowerAt(int x, int y) noexcept; // Removes tower presence on a tile

        void setCoreStorageFillRatioRequest(std::function<float()> callback) noexcept; // Sets the callback to get CoreStorage %fill

        void draw(IVideoRenderer& vidRenderer) const; // Draws the map with margins
    
    private:
        std::string tileToSpriteId(Tile tile) const noexcept; // Converts a tile Type to a sting ID (used to draw)
        std::string randomTextureId(int x, int y) const noexcept; // Gives a random string ID given two integers (used to draw a random texture)
        std::string coreStorageTextureId() const noexcept; // Gives the CoreStorage Tile string ID given its fill level

        int m_width{0};
        int m_height{0};
        std::vector<Tile> m_tiles; // Row-major
        unsigned int m_level{1u}; // For sprite selection

        std::vector<Tile*> m_entryPoints; // Lists entry points for fast access
        std::vector<Tile*> m_exitPoints; // Lists exits points for fast access
        Tile* m_corePoint{nullptr}; // Core storage point for fast access

        std::function<float()> onCoreStorageFillRatioRequest; // Callback to get CoreStorage %fill

        const uint32_t kSeed{0x4470f446u}; // Randomization seed for texture variation
    };

} // namespace tdg::core

#endif // MAP_HPP