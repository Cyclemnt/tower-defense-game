#ifndef COMMAND_BUS_HPP
#define COMMAND_BUS_HPP

#include <queue>
#include <optional>
#include "engine/command.hpp"

namespace tdg::engine {

    class CommandBus {
    public:
        void push(Command c) {
            m_q.push(std::move(c));
        }

        Command pop() {
            Command c = std::move(m_q.front());
            m_q.pop();
            return c;
        }

        bool empty() {
            return m_q.empty();
        }

    private:
        std::queue<Command> m_q;
    };

} // namespace tdg::engine


#endif // COMMAND_BUS_HPP