#ifndef INPUT_CONTROLLER_HPP
#define INPUT_CONTROLLER_HPP

namespace tdg::engine {

    class InputController {
    public:
        virtual ~InputController() = default;

        virtual void handleMouseMove(int x, int y) = 0;
        virtual void handleMouseClick(int x, int y) = 0;
        virtual void handleKey(int key, bool pressed) = 0;
    };

} // namespace tdg::engine

#endif // INPUT_CONTROLLER_HPP