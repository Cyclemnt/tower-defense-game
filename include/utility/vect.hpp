#ifndef VECT_HPP
#define VECT_HPP

namespace tdg::utils {

    template <typename T>
    class Vect2 {
    public:
        T x;
        T y;

        Vect2() : x(T()), y(T()) {}
        Vect2(T x, T y) : x(x), y(y) {}
    };

    using Vect2i = Vect2<int>;
    using Vect2f = Vect2<float>;
    using Vect2u = Vect2<unsigned int>;

} // namespace tdg::utils

#endif // VECT_HPP
