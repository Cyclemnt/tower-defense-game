#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include <memory>
#include <string>
#include "game.hpp"
#include "renderer/renderer.hpp"
#include "gui/guiManager.hpp"

/**
 * @class GameManager
 * @brief Handles the lifecycle of the game: menus, level loading, restarting, and quitting.
 *
 * This class acts as the top-level controller for the entire application.
 * It can:
 * - Load and start a specific level (map + wave configuration).
 * - Manage transitions between main menu, game, and pause states.
 * - Restart or unload a running game.
 */
class GameManager {
public:
    /// @brief Represents the global state of the application.
    enum class State {
        MainMenu,  ///< Player is in the main menu.
        InGame,    ///< A game is currently running.
        Paused,    ///< The game is paused (pause menu active).
        GameOver,  ///< The current game ended.
        Exit       ///< Stop the program.
    };

    /// @brief Represents the available game modes.
    enum class Mode {
        Story,   ///< Loads sequential levels from files (map1.txt, level1.json, etc.)
        Arcade   ///< Loads a single map with automatic waves.
    };

private:
    State state = State::MainMenu;  ///< Current state of the app
    Mode mode = Mode::Story;        ///< Current mode (story or arcade)
    unsigned int currentLevel = 1;  ///< Current level number in story mode

    // --- SFML core ---
    sf::RenderWindow window;
    sf::Clock clock;

    // --- Game objects ---
    std::unique_ptr<Game> game;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<GuiManager> guiManager;

public:
    GameManager();
    
    void run();

private:
    // --- Global state management ---
    [[nodiscard]] State getState() const noexcept { return state; }
    [[nodiscard]] Mode getMode() const noexcept { return mode; }
    [[nodiscard]] bool isInGame() const noexcept { return state == State::InGame; }
    [[nodiscard]] bool isPaused() const noexcept { return state == State::Paused; }

    /// @brief Loads and starts a level with given map and wave files.
    /// @param level The level to load.
    /// @param arcade Whether to use automatic wave generation.
    void loadLevel();

    /// @brief Calls the main menu of the game
    void mainMenu();

    /// @brief Starts the story mode from the first level.
    void startStory();

    /// @brief Starts arcade mode with automatic waves.
    void startArcade();

    /// @brief Restarts the current level from scratch.
    void restartLevel();

    /// @brief Returns to main menu (clears game).
    void returnToMainMenu();

    /// @brief Advances to the next level in story mode.
    void nextLevel();

    /// @brief Main loop
    void gameLoop();
};

#endif // GAME_MANAGER_HPP
