#ifndef MOTHER_HPP
#define MOTHER_HPP

#include "core/creatures/creature.hpp"

namespace tdg::core {
    
    class Mother final : public Creature {
    public:
        explicit Mother(unsigned int level = 1u) noexcept;
        ~Mother() override = default;

        std::string spriteId() const noexcept override;
        void draw(IVideoRenderer& vidRenderer) const override;
    };

} // namespace tdg::core

#endif // MOTHER_HPP