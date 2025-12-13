#include "engine/gameManager.hpp"
#include "infrastructure/fileMapSource.hpp"
#include "infrastructure/autoWaveSource.hpp"
#include "infrastructure/jsonWaveSource.hpp"

#include "infrastructure/sfmlResourceManager.hpp"
#include "infrastructure/sfmlRenderer.hpp"

namespace tdg::engine {
    
    GameManager::GameManager() {
        m_mapSource = std::make_shared<infra::FileMapSource>("../assets/maps/");
        m_waveSource = std::make_shared<infra::JsonWaveSource>("../assets/waves/");

        auto ressources = std::make_shared<infra::SFMLResourceManager>();
        // m_renderer = std::make_shared<infra::SFMLRenderer>(window, ressources);
        // m_gui = std::make_shared<infra::TGUIManager>(window, ressources);
    }

    void GameManager::setState(State state) {
        switch (state) {
        case State::MainMenu:
            /* code */
            break;
        
        case State::Story:
            m_state = State::Loading;
            startStoryMode();
            m_state = State::Story;
            run();
            break;
            
        case State::Arcade:
            m_state = State::Loading;
            startArcadeMode();
            m_state = State::Arcade;
            run();
            break;
            
        case State::Pause:
            m_running = false;
            m_state = State::Pause;
            break;
        
        case State::Resume:
            m_running = true;
            m_state = State::Pause;
            break;

        case State::Victory:
            /* code */
            break;

        case State::GameOver:
            /* code */
            break;

        default:
            break;
        }
    }

    void GameManager::run() {
        m_running = true;
    }

    void GameManager::startStoryMode() {
        m_waveSource = std::make_shared<infra::JsonWaveSource>("../assets/waves/");
        m_level = 1u;
        loadLevel(m_level, m_level);
    }

    void GameManager::startArcadeMode() {
        m_waveSource = std::make_shared<infra::AutoWaveSource>();
        m_level = 1u;
        loadLevel(m_arcadeMapLevel, m_level);
    }

    void GameManager::loadLevel(unsigned int maplvl, unsigned int wavlvl) {
        m_mapSource->setLevel(maplvl);
        m_waveSource->setLevel(wavlvl);
        m_game = std::make_unique<Game>(m_mapSource, m_waveSource);
    }

} // namespace tdg::engine
