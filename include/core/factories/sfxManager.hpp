#ifndef SFX_MANAGER_HPP
#define SFX_MANAGER_HPP

#include "core/events.hpp"
#include "core/interfaces/iAudioRenderer.hpp"

namespace tdg::core {
    
    class SFXManager {
    public:
        SFXManager(std::queue<Events::SFX>& sfxEvents);
        void renderAudio(IAudioRenderer& audRenderer); // Converts the events queue and tells the AudioRenderer to play sounds

    private:
        std::string toString(Events::SFX event) const; // Converts SFX event type to string ID

        std::queue<Events::SFX>& m_sfxEvents;
    };

} // namespace tdg::core

#endif // SFX_MANAGER_HPP
