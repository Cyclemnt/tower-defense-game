#ifndef SFML_AUDIO_RENDERER_HPP
#define SFML_AUDIO_RENDERER_HPP

#include "core/interfaces/iAudioRenderer.hpp"
#include "infrastructure/sfmlResourceManager.hpp"
#include<memory>
namespace tdg::infra {

    class SFMLAudioRenderer : public core::IAudioRenderer {
    public:
        explicit SFMLAudioRenderer(std::shared_ptr<SFMLResourceManager> ressources);

        void playSound(const std::string& soundId) override;

    private:
        void cleanUpFinishedSounds();

        std::shared_ptr<SFMLResourceManager> m_ressources;
        std::vector<std::unique_ptr<sf::Sound>> m_buffer;
    };

} // namespace tdg::infra

#endif // SFML_AUDIO_RENDERER_HPP
