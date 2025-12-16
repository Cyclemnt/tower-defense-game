#ifndef I_GUI_HPP
#define I_GUI_HPP

#include <functional>
#include "core/hudProvider.hpp"
namespace sf { class Event; };
namespace tdg::core { class IVideoRenderer; }

namespace tdg::core {

    class IGUIManager {
    public:
        virtual ~IGUIManager() = default;

        virtual void processEvent(const sf::Event& event) = 0; // We should avoid using sf::Event here but it is convenient

        virtual void showMainMenu() = 0;
        virtual void showHUD() = 0;
        virtual void showPauseMenu() = 0;
        virtual void showGameOver() = 0;
        virtual void showVictory() = 0;

        virtual void update(float dt) = 0;
        virtual void render(core::IVideoRenderer& vidRenderer) = 0;

        virtual void setHUDProvider(core::HUDProvider provider) = 0;

        // Callbacks
        std::function<void()> m_onPause;
        std::function<void()> m_onResume;
        std::function<void()> m_onRestartLevel;
        std::function<void()> m_onQuit;
        std::function<void()> m_onMainMenu;
        std::function<void()> m_onStartStory;
        std::function<void()> m_onStartArcade;
        std::function<void()> m_onNextLevel;
    };

} // namespace tdg::core

#endif // I_GUI_HPP