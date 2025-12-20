#include "core/managers/sfxManager.hpp"

#include "core/events.hpp"
#include "core/interfaces/iAudioRenderer.hpp"

namespace tdg::core {

    SFXManager::SFXManager(std::queue<Events::NewSFX>& sfxEvents)
        : m_sfxEvents(sfxEvents) {}
    
    void SFXManager::renderAudio(IAudioRenderer& audRenderer) {
        while (!m_sfxEvents.empty()) {
            audRenderer.playSound(toString(m_sfxEvents.front()));
            m_sfxEvents.pop();
        }
    }

    std::string SFXManager::toString(Events::NewSFX event) const {
        Events::NewSFX::Type type = event.type;
        unsigned int level = event.level;
        switch (type) {
            case Events::NewSFX::Type::GatlingShoot:  return "gatling_shoot_" + std::to_string(level);
            case Events::NewSFX::Type::LaserShoot:    return "laser_shoot_" + std::to_string(level);
            case Events::NewSFX::Type::MortarShoot:   return "mortar_shoot_" + std::to_string(level);
            case Events::NewSFX::Type::MortarHit:     return "mortar_hit_" + std::to_string(level);
            case Events::NewSFX::Type::CreatureSpawn: return "spawn";
            case Events::NewSFX::Type::CreatureDeath: return "death";
            case Events::NewSFX::Type::CoreSteal:     return "core_steal";
            case Events::NewSFX::Type::LevelCompleted: return "level_completed";
            case Events::NewSFX::Type::GameOver:       return "game_over";
            case Events::NewSFX::Type::NextWave:       return "next_wave";
        }
        return "";
    }

} // namespace tdg::core
