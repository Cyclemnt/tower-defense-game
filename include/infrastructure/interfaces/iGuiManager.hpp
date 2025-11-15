#ifndef I_GUI_HPP
#define I_GUI_HPP

#include <string>
#include <chrono>

namespace tdg::infra {

    class IGUIManager {
    public:
        virtual ~IGUIManager() = default;

        virtual void showMainMenu() = 0;
        virtual void showHUD() = 0;
        virtual void showPauseMenu() = 0;
        virtual void showGameOver() = 0;
        virtual void showVictory() = 0;

        virtual void update(std::chrono::milliseconds dt) = 0;
        virtual void render() = 0;
    };

} // namespace tdg::infra

#endif // I_GUI_HPP