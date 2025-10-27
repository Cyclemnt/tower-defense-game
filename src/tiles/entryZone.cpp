#include "../../include/tiles/entryZone.hpp"

EntryZone::EntryZone(sf::Vector2i position_)
    : Tile(position_) {}

EntryZone::~EntryZone() {}

bool EntryZone::isWalkable() const { return true; }

bool EntryZone::isBuildable() const { return false; }

std::string EntryZone::getTextureName() const { return "tile_entry.png"; }
