#ifndef SFML_AUDIO_RENDERER_HPP
#define SFML_AUDIO_RENDERER_HPP

#include <SFML/Graphics.hpp>
#include "infrastructure/interfaces/iAudioRenderer.hpp"
#include "infrastructure/sfmlResourceManager.hpp"

namespace tdg::infra {

    class SFMLAudioRenderer : public IAudioRenderer {
    public:
        explicit SFMLAudioRenderer(std::shared_ptr<SFMLResourceManager> ressources);

        void playSound(const std::string& soundId) override;

    private:
        std::shared_ptr<SFMLResourceManager> m_ressources;
    };

} // namespace tdg::infra

#endif // SFML_AUDIO_RENDERER_HPP
