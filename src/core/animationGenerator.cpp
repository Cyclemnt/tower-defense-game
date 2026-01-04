#include <cstdlib>
#include <ctime>
#include "core/animationGenerator.hpp"
#include "core/map.hpp"
#include "core/events.hpp"

namespace tdg::core {
    
    AnimationGenerator::AnimationGenerator(Map& map)
        : m_map(map)
    {
        std::srand(std::time(nullptr));
    }

    void AnimationGenerator::generate(float dt, Events& events) {
        int rnd = std::rand() % 1000;
        
        unsigned int level = m_map.level();
        int mapW = m_map.width();
        int mapH = m_map.height();

        int rndX = std::rand() % (mapW + 10) - 5;
        int rndY = std::rand() % (mapH + 10) - 5;

        if (m_map.tileAt(rndX, rndY) && m_map.tileAt(rndX, rndY)->walkable(true)) return; // No animation on walkable tiles
        
        switch (level) {
            case 1u: if (rnd < 2) events.vfxs.emplace(Events::NewVFX::Type::Fanuc, level, rndX, rndY); break;
            case 2u: break;
            case 3u: break;
            case 4u: break;
            case 5u: if (rnd < 20) events.vfxs.emplace(Events::NewVFX::Type::FireFly, level, rndX, rndY); break;
            
            default: break;
        }
    }

} // namespace tdg::core
