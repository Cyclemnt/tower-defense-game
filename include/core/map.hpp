#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <memory>
#include <string>

namespace tdg::core { class IMapSource; class IVideoRenderer; }

namespace tdg::core {

    struct Tile {
        enum class Type { Path, Open, Entry, Exit, CoreStorage, Empty };

        int x{0}, y{0};
        Type type{Type::Empty};
        bool hasTower{false};

        Tile(int px = 0, int py = 0, Type t = Type::Empty) : x(px), y(py), type(t) {}
        bool walkable(bool ignoreTower) const { return (type != Type::Empty && (ignoreTower || !hasTower)); }
        bool buildable() const { return (type == Type::Open && !hasTower); }
        bool sellable() const { return (type == Type::Open && hasTower); }
    };

    /// @brief Map stores tile layout and provides queries. Domain-only.
    class Map {
    public:
        explicit Map(std::shared_ptr<IMapSource> source);

        int width() const noexcept { return m_width; }
        int height() const noexcept { return m_height; }

        const Tile* tileAt(int x, int y) const;
        Tile* tileAt(int x, int y);

        std::vector<const Tile*> neighbors(const Tile* tile) const;

        std::vector<Tile*> entryPoints() const noexcept { return m_entryPoints; }
        std::vector<Tile*> exitPoints() const noexcept { return m_exitPoints; }
        Tile* corePoint() const noexcept { return m_corePoint; }

        bool placeTower(int x, int y);
        bool removeTower(int x, int y);

        void setCoreStorageFillRatio(float ratio);

        void draw(IVideoRenderer& vidRenderer) const;
    
    private:
        std::string tileToSpriteId(Tile t) const;
        std::string randomTextureId(int x, int y) const noexcept;
        std::string coreStorageTextureId() const noexcept;

        int m_width{0};
        int m_height{0};
        std::vector<Tile> m_tiles; // row-major

        std::vector<Tile*> m_entryPoints;
        std::vector<Tile*> m_exitPoints;
        Tile* m_corePoint{nullptr};

        float coreStorageFillRatio{1.0f};

        const uint32_t kSeed{0x4470f446u}; ///< Randomization seed for texture variation
    };

} // namespace tdg::core

#endif // MAP_HPP