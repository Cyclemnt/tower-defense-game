#ifndef I_COMMAND_HANDLER_HPP
#define I_COMMAND_HANDLER_HPP

#include "engine/command.hpp"

namespace tdg::engine {

    class ICommandHandler {
    public:
        virtual ~ICommandHandler() = default;
        virtual void handleCommand(const Command& cmd) = 0;
    };

} // namespace tdg::engine

#endif // I_COMMAND_HANDLER_HPP