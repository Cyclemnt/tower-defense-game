#ifndef COLOR_HPP
#define COLOR_HPP

namespace tdg::utils {

    class Color {
    public:
        unsigned int r{255}, g{255}, b{255}, a{255};

        Color() = default;

        Color(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha = 255u)
            : r(red), g(green), b(blue), a(alpha) {}

        void setColor(unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha = 255u) {
            r = clamp(red);
            g = clamp(green);
            b = clamp(blue);
            a = clamp(alpha);
        }

    private:
        unsigned int clamp(unsigned int value) const {
            return (value > 255) ? 255 : (value < 0) ? 0 : value;
        }
    };

    const Color White(255, 255, 255, 255);

} // namespace tdg::utils

#endif // COLOR_HPP
