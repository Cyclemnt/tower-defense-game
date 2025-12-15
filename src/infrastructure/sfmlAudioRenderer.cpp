#include <SFML/Audio.hpp>
#include "infrastructure/sfmlAudioRenderer.hpp"
#include <memory>
namespace tdg::infra {

    SFMLAudioRenderer::SFMLAudioRenderer(std::shared_ptr<SFMLResourceManager> ressources)
        : m_ressources(ressources) {}

    void SFMLAudioRenderer::playSound(const std::string& soundId) {
        try {
            const sf::SoundBuffer& buffer = m_ressources->getSound(soundId);
            std::unique_ptr<sf::Sound> s = std::make_unique<sf::Sound>(buffer);
            s->play();
            m_buffer.push_back(std::move(s));
        }
        catch (...) {}
    }

    void SFMLAudioRenderer::cleanUpFinishedSounds() {
        for (auto it = m_buffer.begin(); it != m_buffer.end();) {
            if ((*it)->getStatus() == sf::Sound::Status::Stopped) {
                it = m_buffer.erase(it);
            } else { ++it; }
        }
    }

} // namespace tdg::infra
