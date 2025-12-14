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
        class Spawn {
        public:
            Creature::Type type;
            std::optional<unsigned int> entrance;
        };

        // Path event
        class Path {
        public:
            enum class Type {
                ArrivedToCore,   // When creature reaches core storage
                ArrivedToExit,   // When creature reaches exit
            };

            Path::Type type; // Event type
            Creature* creature;   // Ref to the creature

            Path(Path::Type t, Creature* c) : type(t), creature(c) {}
        };
        
        // SFX Event
        class SFX {
        public:
            enum class Type {
                CreatureSpawn,
                CreatureDeath,
                GatlingShoot,
                LaserShoot,
                MortarShoot,
                MortarHit
            };
            
            SFX::Type type;

            SFX(SFX::Type t) : type(t) {}

            std::string toString() const {
                switch (type) {
                    case SFX::Type::CreatureSpawn: return "sounds/spawn";
                    case SFX::Type::CreatureDeath: return "sounds/death";
                    case SFX::Type::GatlingShoot:  return "sounds/gatling";
                    case SFX::Type::LaserShoot:    return "sounds/laser";
                    case SFX::Type::MortarShoot:   return "sounds/mortar";
                    case SFX::Type::MortarHit:     return "sounds/explosion";
                }
                return "";
            }
        };

        // VFX Event
        class VFX {
        public:
            enum class Type {
                LaserBeam,
                GatlingTracer,
                HitSpark,
                Explosion
            };

            VFX::Type type;
            unsigned int level;
            float xStart, yStart;
            std::optional<float> xEnd, yEnd;

            VFX(VFX::Type t, unsigned int lvl, float x1, float y1, std::optional<float> x2 = std::nullopt, std::optional<float> y2 = std::nullopt) 
                : type(t), level(lvl), xStart(x1), yStart(y1), xEnd(x2), yEnd(y2) {}
        };

        // Events queues
        std::queue<SFX> sfxs;
        std::queue<VFX> vfxs;
        std::queue<Path> path;
        std::queue<Spawn> spawn;
    };

} // namespace tdg::core

#endif // EVENTS_HPP