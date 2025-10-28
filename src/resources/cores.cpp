#include <cmath>
#include "../../include/resources/cores.hpp"

Cores::Cores(unsigned int initial) noexcept
    : safe(initial) {}

unsigned int Cores::stealCore(unsigned int n) noexcept {
    const unsigned int taken = std::min(n, safe);
    safe   -= taken;
    stolen += taken;
    return taken;
}

void Cores::returnCore(unsigned int n) noexcept {
    if (n > stolen) n = stolen;
    stolen -= n;
    safe   += n;
}

void Cores::loseCore(unsigned int n) noexcept {
    if (n > stolen) n = stolen;
    stolen -= n;
    lost   += n;
}