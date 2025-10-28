#include <cmath>
#include "../../include/resources/cores.hpp"

Cores::Cores(unsigned int initial)
    : safe(initial) {}

Cores::~Cores() {}

unsigned int Cores::stealCore(unsigned int n) {
    int taken = std::min(n, safe);
    safe -= taken;
    stolen += taken;
    return taken;
}

void Cores::returnCore(unsigned int n) {
    stolen -= n;
    safe += n;
}

void Cores::loseCore(unsigned int n) {
    stolen -= n;
    lost += n;
}
