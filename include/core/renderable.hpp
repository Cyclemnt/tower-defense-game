#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

namespace tdg::core { class IVideoRenderer; }

namespace tdg::core {
    
    class Renderable {
    public:
        virtual float zOrder() const noexcept = 0; // Used to sort before rendering (higher : in front of)
        virtual int drawLayer() const { return 0; } // Used for priority between two equal zOrder (higher : in front of)
        virtual void draw(IVideoRenderer& vidRenderer) const = 0; // Draws the renderable
    };

} // namespace tdg::core

#endif // RENDERABLE_HPP