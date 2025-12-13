#ifndef I_AUDIO_RENDERER_HPP
#define I_AUDIO_RENDERER_HPP

namespace tdg::infra {

    class IAudioRenderer {
    public:
        virtual ~IAudioRenderer() = default;

        virtual void playSound(const std::string& soundId) = 0;
    };

} // namespace tdg::infra

#endif // I_AUDIO_RENDERER_HPP