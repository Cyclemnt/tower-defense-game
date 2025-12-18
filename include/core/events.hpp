#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <vector>
#include <queue>
#include <string>
#include <optional>
#include "core/creatures/creature.hpp"

namespace tdg::core {

    // Event collector
    class Events {
    public:

        // Spawn Event
        struct Spawn {
            Creature::Type type;
            unsigned int level;
            std::optional<unsigned int> entrance;
        };

        // Path event
        struct Path {
            enum class Type {
                ArrivedToCore, // When creature reaches core storage
                ArrivedToExit, // When creature reaches exit
            };

            Path(Path::Type t, Creature* c) : type(t), creature(c) {}

            Path::Type type; // Event type
            Creature* creature; // Ref to the creature
        };
        
        // SFX Event
        struct SFX {
            enum class Type {
                CreatureSpawn, CreatureDeath, CoreSteal,
                GatlingShoot, LaserShoot, MortarShoot, MortarHit,
                LevelCompleted, GameOver, NextWave
            };

            SFX(SFX::Type t, unsigned int lvl = 1u) : type(t), level(lvl) {}
            
            SFX::Type type;
            unsigned int level;
        };

        // VFX Event
        struct VFX {
            enum class Type { LaserBeam, GatlingTracer, HitSpark, Explosion };

            VFX(VFX::Type t, unsigned int lvl, float x1, float y1, std::optional<float> x2 = std::nullopt, std::optional<float> y2 = std::nullopt) 
                : type(t), level(lvl), xStart(x1), yStart(y1), xEnd(x2), yEnd(y2) {}

            VFX::Type type;
            unsigned int level;
            float xStart, yStart;
            std::optional<float> xEnd, yEnd;
        };

        // Events queues
        std::queue<SFX> sfxs;
        std::queue<VFX> vfxs;
        std::queue<Path> path;
        std::queue<Spawn> spawn;
    };

} // namespace tdg::core

#endif // EVENTS_HPP