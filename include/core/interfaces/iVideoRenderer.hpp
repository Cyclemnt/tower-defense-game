#ifndef I_VIDEO_RENDERER_HPP
#define I_VIDEO_RENDERER_HPP

#include <string>

namespace tdg::core {

    class IVideoRenderer {
    public:
        virtual ~IVideoRenderer() = default;

        virtual void drawSprite(const std::string& spriteId, float x, float y) = 0;
        virtual void drawRectangle(float x, float y, float width, float height, int red, int green, int blue, int alpha = 255u) = 0;
        virtual void drawRectangle(float x1, float y1, float x2, float y2, float width, int red, int green, int blue, int alpha = 255u) = 0;
        virtual void drawCircle(float x, float y, float radius, int red, int green, int blue, int alpha = 255u) = 0;
    };

} // namespace tdg::core

#endif // I_VIDEO_RENDERER_HPP