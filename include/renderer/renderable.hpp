#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

class RenderContext;

class IRenderable {
public:
    virtual ~IRenderable() = default;
    virtual void render(const RenderContext& ctx) const = 0;
};

#endif // RENDERABLE_HPP