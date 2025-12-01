#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <vector>
#include <optional>

namespace tdg::core {

    // Event collector
    struct Events {
        std::vector<SFXType> sfxs;
        std::vector<VFXEventData> vfxs;
        std::vector<PathEvent> pathEvents;

        void update(float dt) {
            for (auto it = vfxs.begin(); it != vfxs.end(); ) {
                if (it->lifeTime -= dt <= 0) it = vfxs.erase(it);
                else ++it;
            }
        }
    };

    struct PathEvent {
        enum class Type {
            ArrivedToCore,   // Quand la créature atteint CoreStorage
            ArrivedToExit,   // Quand la créature atteint Exit
        };

        PathEvent::Type type; // Type d'événement (changement de chemin, etc.)
        Creature* creature;   // Référence à la créature concernée

        PathEvent(PathEvent::Type t, Creature* c)
            : type(t), creature(c) {}
    };
    
    enum class SFXType {
        CreatureSpawn,
        CreatureDeath,
        GatlingShoot,
        LaserShoot,
        MortarShoot,
        MortarHit
    };

    enum class VFXType {
        LaserBeam,
        GatlingTracer,
        HitSpark,
        Explosion
    };

    struct VFXEventData {
        VFXType type;
        float lifeTime;
        float xStart, yStart;
        std::optional<float> xEnd, yEnd;

        VFXEventData(VFXType t, float x, float y, float lt = 0.0f) 
            : type(t), xStart(x), yStart(y), xEnd(std::nullopt), yEnd(std::nullopt), lifeTime(lt) {}

        VFXEventData(VFXType t, float x1, float y1, float x2, float y2, float lt = 0.0f) 
            : type(t), xStart(x1), yStart(y1), xEnd(x2), yEnd(y2), lifeTime(lt) {}
    };

} // namespace tdg::core

#endif // EVENTS_HPP