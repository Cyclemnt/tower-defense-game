#ifndef I_GAME_HPP
#define I_GAME_HPP

#include <optional>
#include <string>

namespace tdg::core { class Materials; }

namespace tdg::engine {

    struct CoresState {
        unsigned int safe;
        unsigned int stolen;
        unsigned int lost;
    };

    struct WaveState {
       unsigned int currentWave;
        unsigned int totalWaves;
        unsigned int timeToNext;
    };
    
    class IGame {
    public:
        virtual bool tileOpenAt(int x, int y) const = 0;
        virtual bool towerAt(int x, int y) const = 0;
        virtual std::optional<float> towerRangeAt(int x, int y) const = 0;
        virtual std::optional<core::Materials> towerCost(std::string towerType) const = 0;
        virtual bool canAfford(std::string towerType) const = 0;

        virtual core::Materials playerBalance() const noexcept = 0;
        virtual CoresState coresState() const noexcept = 0;
        virtual WaveState waveState() const noexcept = 0;

        virtual int mapWidth() const = 0;
        virtual int mapHeight() const = 0;
    };
    
} // namespace tdg::engine

#endif // I_GAME_HPP