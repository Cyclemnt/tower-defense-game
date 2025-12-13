#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <vector>
#include <queue>
#include <optional>
#include "core/creatures/creature.hpp"

namespace tdg::core {

    struct SpawnInfo {
        Creature::Type type;
        std::optional<unsigned int> entrance;
    };

    struct PathEvent {
        enum class Type {
            ArrivedToCore,   // When creature reaches core storage
            ArrivedToExit,   // When creature reaches exit
        };

        PathEvent::Type type; // Event type
        Creature* creature;   // Ref to the creature

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
        unsigned int level;
        float lifeTime;
        float xStart, yStart;
        std::optional<float> xEnd, yEnd;

        VFXEventData(VFXType t, float x, float y, float lt = 0.0f) 
            : type(t), xStart(x), yStart(y), xEnd(std::nullopt), yEnd(std::nullopt), lifeTime(lt) {}

        VFXEventData(VFXType t, float x1, float y1, float x2, float y2, float lt = 0.0f) 
            : type(t), xStart(x1), yStart(y1), xEnd(x2), yEnd(y2), lifeTime(lt) {}
    };

    // Event collector
    class Events {
    public:
        std::queue<SFXType> sfxs;
        std::queue<VFXEventData> vfxs;
        std::queue<PathEvent> pathEvents;
        std::queue<SpawnInfo> spawn;
    };

} // namespace tdg::core

#endif // EVENTS_HPP