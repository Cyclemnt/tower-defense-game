#include "../include/gameManager.hpp"
#include "../include/map/txtMapSource.hpp"
#include "../include/waves/autoWaveSource.hpp"
#include "../include/waves/jsonWaveSource.hpp"
#include <iostream>

GameManager::GameManager() {
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.create(desktop, "Tower Defense", sf::State::Fullscreen);
    window.setFramerateLimit(60);
}

void GameManager::run() {
    bool running = true;

    while (running && window.isOpen()) {
        switch (state) {
            case State::MainMenu:
                mainMenu();
                break;
            case State::InGame:
                gameLoop();
                break;
            case State::Exit:
                running = false;
                break;
        }
    }
}

void GameManager::mainMenu() {
    // For now, start arcade
    startStory();
}

void GameManager::loadLevel() {
    try {
        // Load map
        unsigned int initialCores = 24u;
        std::unique_ptr<IMapSource> mapSource = std::make_unique<TxtMapSource>("../assets/maps/map" + std::to_string(currentLevel) + ".txt");

        // Create wave source
        std::unique_ptr<IWaveSource> waveSource;
        switch (mode) {
        case Mode::Story:
            waveSource = std::make_unique<JsonWaveSource>("../assets/waves/level" + std::to_string(currentLevel) + ".json");
            break;
        case Mode::Arcade:
            [[fallthrough]];
        default:
            waveSource = std::make_unique<AutoWaveSource>();
            break;
        }

        // Build Game
        game = std::make_unique<Game>(std::move(mapSource), std::move(waveSource), initialCores);

        // Rebuild rendering systems
        renderer = std::make_unique<Renderer>(window, *game);
        guiManager = std::make_unique<GuiManager>(window, *game, renderer->getContext());

        state = State::InGame;
        std::cout << "[GameManager] Loaded level: " << currentLevel << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "[GameManager] Failed to load level: " << e.what() << std::endl;
        state = State::MainMenu;
    }
}

void GameManager::startStory() {
    mode = Mode::Story;
    currentLevel = 1;
    loadLevel();
}

void GameManager::startArcade() {
    mode = Mode::Arcade;
    loadLevel();
}

void GameManager::restartLevel() {
    loadLevel();
}

void GameManager::returnToMainMenu() {
    game.reset();
    state = State::MainMenu;
    std::cout << "[GameManager] Returned to main menu.\n";
}

void GameManager::nextLevel() {
    if (mode != Mode::Story) return;

    ++currentLevel;
    loadLevel();
}

void GameManager::gameLoop() {
    while (window.isOpen() && state == State::InGame) {
        // --- Events ---
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                return;
            }
            guiManager->processEvent(*event);
        }

        // --- Update ---
        float dt = clock.restart().asSeconds();
        if (!game->isPaused()) game->update(dt);

        // --- Render ---
        window.clear();
        renderer->render();
        guiManager->draw(dt);
        window.display();
    }
}