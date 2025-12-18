#include "core/factories/sfxManager.hpp"

namespace tdg::core {

    SFXManager::SFXManager(std::queue<Events::SFX>& sfxEvents)
        : m_sfxEvents(sfxEvents) {}
    
    void SFXManager::renderAudio(IAudioRenderer& audRenderer) {
        while (!m_sfxEvents.empty()) {
            audRenderer.playSound(toString(m_sfxEvents.front()));
            m_sfxEvents.pop();
        }
    }

    std::string SFXManager::toString(Events::SFX event) const {
        Events::SFX::Type type = event.type;
        unsigned int level = event.level;
        switch (type) {
            case Events::SFX::Type::GatlingShoot:  return "gatling_shoot_" + std::to_string(level);
            case Events::SFX::Type::LaserShoot:    return "laser_shoot_" + std::to_string(level);
            case Events::SFX::Type::MortarShoot:   return "mortar_shoot_" + std::to_string(level);
            case Events::SFX::Type::MortarHit:     return "mortar_hit_" + std::to_string(level);
            case Events::SFX::Type::CreatureSpawn: return "spawn";
            case Events::SFX::Type::CreatureDeath: return "death";
            case Events::SFX::Type::CoreSteal:     return "core_steal";
            case Events::SFX::Type::LevelCompleted: return "level_completed";
            case Events::SFX::Type::GameOver:       return "game_over";
            case Events::SFX::Type::NextWave:       return "next_wave";
        }
        return "";
    }

} // namespace tdg::core
