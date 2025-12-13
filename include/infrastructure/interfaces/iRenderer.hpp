#ifndef I_RENDERER_HPP
#define I_RENDERER_HPP

namespace tdg::infra {

    class IRenderer {
    public:
        virtual ~IRenderer() = default;

        virtual void drawSprite(const std::string& spriteId, float x, float y) = 0;
        virtual void drawRectangle(float x, float y, float width, float height, int red, int green, int blue, int alpha) = 0;
        virtual void drawRectangle(float x1, float y1, float x2, float y2, float width, int red, int green, int blue, int alpha) = 0;
        virtual void drawCircle(float x, float y, float radius, int red, int green, int blue, int alpha) = 0;
    };

} // namespace tdg::infra

#endif // I_RENDERER_HPP