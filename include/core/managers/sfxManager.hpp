#ifndef SFX_MANAGER_HPP
#define SFX_MANAGER_HPP

#include "core/events.hpp"

namespace tdg::core { class Events; class IAudioRenderer; };

namespace tdg::core {
    
    class SFXManager {
    public:
        SFXManager(std::queue<Events::NewSFX>& sfxEvents);
        void renderAudio(IAudioRenderer& audRenderer); // Converts the events queue and tells the AudioRenderer to play sounds

        void update(float dt, Events& events); // Main function to create new SFXs and update them

    private:
        std::string toString(Events::NewSFX event) const; // Converts SFX event type to string ID

        std::queue<Events::NewSFX>& m_sfxEvents; // maybe create a SFX class just like VFX?
    };

} // namespace tdg::core

#endif // SFX_MANAGER_HPP
