#include "../../include/resources/cores.hpp"
#include <cmath>

Cores::Cores(int initial)
    : safe(initial), stolen(0), lost(0) {}

Cores::~Cores() {}

int Cores::getSafe() const { return safe; }
int Cores::getStolen() const { return stolen; }
int Cores::getLost() const { return lost; }

int Cores::stealCore(int n) {
    if (n <= 0) return 0;
    int taken = std::min(n, safe);
    safe -= taken;
    stolen += taken;
    return taken;
}

void Cores::returnCore(int n) {
    if (n <= 0) return;
    stolen -= n;
    safe += n;
}

void Cores::loseCore(int n) {
    if (n <= 0) return;
    stolen -= n;
    lost += n;
}
