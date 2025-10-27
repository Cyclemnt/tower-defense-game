#include "../../include/tiles/exitZone.hpp"

ExitZone::ExitZone(sf::Vector2i position_)
    : Tile(position_) {}

ExitZone::~ExitZone() {}

bool ExitZone::isWalkable() const { return true; }

bool ExitZone::isBuildable() const { return false; }

std::string ExitZone::getTextureName() const { return "tile_exit.png"; }
