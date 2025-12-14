#include <SFML/Audio.hpp>
#include "infrastructure/sfmlAudioRenderer.hpp"

namespace tdg::infra {

    SFMLAudioRenderer::SFMLAudioRenderer(std::shared_ptr<SFMLResourceManager> ressources)
        : m_ressources(ressources) {}

    void SFMLAudioRenderer::playSound(const std::string& soundId) {
        const sf::SoundBuffer& buffer = m_ressources->getSound(soundId);
        sf::Sound sound(buffer);
        sound.play();
    }

} // namespace tdg::infra
