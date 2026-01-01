#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/System.hpp>
#include "core/interfaces/iVideoRenderer.hpp"
#include "engine/game.hpp"

namespace tdg::engine {
    
    class HUD {
    public:
        HUD();

        void update(float dt);
        void draw(core::IVideoRenderer& vidRenderer);

        void setGamePtr(std::weak_ptr<Game> game);

    private:
        void drawResourcesPanel(core::IVideoRenderer& vidRenderer) const;
        void drawCores(core::IVideoRenderer& vidRenderer) const;
        void drawWavePanel(core::IVideoRenderer& vidRenderer) const;
        void drawFPSPanel(core::IVideoRenderer& vidRenderer) const;
        
        std::weak_ptr<Game> m_game;

        sf::Clock m_fpsClock;   ///< Small clock used to throttle FPS calculation
        float m_lastFPS{0.0f};  ///< Last computed FPS value (integer-ish for display)
    };

} // namespace tdg::engine

#endif // HUD_HPP