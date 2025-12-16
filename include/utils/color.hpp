#ifndef COLOR_HPP
#define COLOR_HPP

#include <algorithm>

namespace tdg::utils {

    class Color {
    public:
        unsigned int r{255}, g{255}, b{255}, a{255};

        void setColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha = 255u) {
            r = std::clamp(red, 0u, 255u);
            g = std::clamp(green, 0u, 255u);
            b = std::clamp(blue, 0u, 255u);
            a = std::clamp(alpha, 0u, 255u);
        }
    };
    
} // namespace tdg::utils

#endif // COLOR_HPP
