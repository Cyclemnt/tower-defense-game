#ifndef I_VIDEO_RENDERER_HPP
#define I_VIDEO_RENDERER_HPP

#include <string>
#include "utility/color.hpp"

namespace tdg::core {

    class IVideoRenderer {
    public:
        virtual ~IVideoRenderer() = default;

        virtual void drawSprite(const std::string& spriteId, float x, float y, float size = 1.0f, utils::Color color = {0u,0u,0u,0u}, bool worldCoordinates = true) = 0;
        virtual void drawRectangle(float x, float y, float width, float height, utils::Color fill, float thickness = 0.0f, utils::Color outline = {0u,0u,0u,0u}, bool worldCoordinates = true) = 0;
        virtual void drawLine(float x1, float y1, float x2, float y2, float width, utils::Color fill, float thickness = 0.0f, utils::Color outline = {0u,0u,0u,0u}, bool worldCoordinates = true) = 0;
        virtual void drawCircle(float x, float y, float radius, utils::Color fill, float thickness = 0.0f, utils::Color outline = {0u,0u,0u,0u}, bool worldCoordinates = true) = 0;
        virtual void drawText(const std::string& text, float size, float x, float y, utils::Color color, bool worldCoordinates = true) = 0;

        virtual unsigned int getWindowWidth() const = 0;
        virtual unsigned int getWindowHeight() const = 0;
    };

} // namespace tdg::core

#endif // I_VIDEO_RENDERER_HPP