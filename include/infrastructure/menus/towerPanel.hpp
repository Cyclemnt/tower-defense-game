#ifndef TOWER_PANEL_HPP
#define TOWER_PANEL_HPP

#include "core/interfaces/iVideoRenderer.hpp"
#include "core/gameViewProvider.hpp"

namespace tdg::infra {

    class TowerPanel {
    public:
        TowerPanel();

        void draw(core::IVideoRenderer& vidRenderer);
    
        void setProvider(core::GameViewProvider provider);

    private:
        void drawBackPanel(core::IVideoRenderer& vidRenderer);
        void drawTowers(core::IVideoRenderer& vidRenderer);
        void drawCosts(core::IVideoRenderer& vidRenderer);
        void drawUpgradeBtn(core::IVideoRenderer& vidRenderer);
        void drawSellBtn(core::IVideoRenderer& vidRenderer);
        
        float m_scale{0.0f};
        unsigned int m_winX{0u};
        unsigned int m_winY{0u};

        float m_panelW{0.0f};
        float m_panelH{0.0f};
        float m_panelX{0.0f};
        float m_panelY{0.0f};
        
        core::GameViewProvider m_provider;
    };

} // namespace tdg::infra

#endif // TOWER_PANEL_HPP