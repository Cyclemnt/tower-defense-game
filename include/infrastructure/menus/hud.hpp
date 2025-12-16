#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include "core/interfaces/iVideoRenderer.hpp"
#include "core/hudProvider.hpp"

namespace tdg::infra {
    
    class HUD {
    public:
        HUD();

        void update(float dt);
        void draw(core::IVideoRenderer& vidRenderer);

        void setProvider(core::HUDProvider provider);

    private:
        void drawResourcesPanel(core::IVideoRenderer& vidRenderer) const;
        void drawCores(core::IVideoRenderer& vidRenderer) const;
        void drawWavePanel(core::IVideoRenderer& vidRenderer) const;
        void drawFPSPanel(core::IVideoRenderer& vidRenderer) const;

        sf::Clock m_fpsClock;   ///< Small clock used to throttle FPS calculation
        float m_lastFPS{0.0f};  ///< Last computed FPS value (integer-ish for display)
        float m_scale{0.0f};
        unsigned int m_winX{0u};
        unsigned int m_winY{0u};

        core::HUDProvider m_provider;
    };

} // namespace tdg::infra

#endif // HUD_HPP