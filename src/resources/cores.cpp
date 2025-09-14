#include "../../include/resources/cores.hpp"

Cores::Cores(int initial)
    : safe(initial), stolen(0), lost(0) {}

Cores::~Cores() {}

// Enemy steals cores from base
void Cores::stealCore(int n) {
    safe -= n;
    stolen += n;
}

// Enemy carrying cores dies → cores return
void Cores::returnCore(int n) {
    stolen -= n;
    safe += n;
}

// Enemy exits with cores → they are permanently lost
void Cores::loseCore(int n) {
    stolen -= n;
    lost += n;
}
