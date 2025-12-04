#include "engine/game.hpp"
#include "infrastructure/fileMapSource.hpp"
#include "infrastructure/autoWaveSource.hpp"
#include "infrastructure/aStarPathfinder.hpp"
#include "core/interfaces/iWaveSource.hpp"
#include "core/interfaces/iPathfinder.hpp"

int main() {
    tdg::infra::FileMapSource fms("../assets/maps/");
    tdg::core::Map map(fms.loadMap(1u));
    std::unique_ptr<tdg::core::IWaveSource> aws = std::make_unique<tdg::infra::AutoWaveSource>(3);
    std::shared_ptr<tdg::core::IPathfinder> asp = std::make_shared<tdg::infra::AStarPathfinder>(map);
    tdg::core::Materials mat = {0u, 150u, 150u};
    unsigned int sc = 24u;
    tdg::engine::Game::Config cfg = {map, std::move(aws), asp, mat, sc};

    tdg::engine::Game game(std::move(cfg));

    for (int i = 0; i < 100; i++) {
        game.update(0.2);
    }
    
    
    return 0;
}
