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
        
        // SFX Event
        struct NewSFX {
            enum class Type {
                CreatureSpawn, CreatureDeath, CoreSteal,
                GatlingShoot, LaserShoot, MortarShoot, MortarHit,
                LevelCompleted, GameOver, NextWave
            };

            NewSFX(NewSFX::Type t, unsigned int lvl = 1u) : type(t), level(lvl) {}
            
            NewSFX::Type type;
            unsigned int level;
        };

        // VFX Event
        struct NewVFX {
            enum class Type { LaserBeam, GatlingTracer, HitSpark, Explosion, Fanuc, FireFly, Butterfly, Pipou, Tumbleweed };

            NewVFX(NewVFX::Type t, unsigned int lvl, float x1 = 0.0f, float y1 = 0.0f, std::optional<float> x2 = std::nullopt, std::optional<float> y2 = std::nullopt) 
                : type(t), level(lvl), xStart(x1), yStart(y1), xEnd(x2), yEnd(y2) {}

            NewVFX::Type type;
            unsigned int level;
            float xStart, yStart;
            std::optional<float> xEnd, yEnd;
        };

        // Events happening on Creatures Paths
        struct OnPath {
            enum class Type { ArrivedAtCore, ReachedExit };

            OnPath(OnPath::Type t, Creature* c) : type(t), creature(c) {}

            OnPath::Type type;
            Creature* creature;
        };

        // Cores dropped by dead creatures
        struct DroppedCores {
            unsigned int dropped;
            float x, y;

            DroppedCores(unsigned int amount, float px, float py) : x(px), y(py), dropped(amount) {}
        };

        // Events queues
        std::queue<NewSFX> sfxs;
        std::queue<NewVFX> vfxs;
        std::queue<Spawn> spawn;
        std::queue<OnPath> onPath;
        
        std::queue<DroppedCores> droppedCores;
    };

} // namespace tdg::core

#endif // EVENTS_HPP