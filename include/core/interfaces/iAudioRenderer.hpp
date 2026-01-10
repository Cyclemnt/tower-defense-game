#ifndef I_AUDIO_RENDERER_HPP
#define I_AUDIO_RENDERER_HPP

#include <string>

namespace tdg::core {

    class IAudioRenderer {
    public:
        virtual ~IAudioRenderer() = default;

        virtual void playSound(const std::string& soundId) = 0;

        virtual void setPitch(float pitch) { m_pitch = pitch; }

    protected:
        float m_pitch{1.0f};
    };

} // namespace tdg::core

#endif // I_AUDIO_RENDERER_HPP