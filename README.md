# Tower Defense Game
A simplified tower defense game in C++

## Game Concept
- The game is played on a top-down map.
- A resource of limited quantity must be defended from waves of creatures.
- Creatures spawn in predefined entry zones and attempt to reach the resource via
the shortest path.
- If a creature reaches the resource, it steals one unit and tries to escape through
predefined exit zones, again using the shortest path.
- The player builds defense towers to destroy or slow creatures. Towers vary by
type and level.
- Building towers consumes materials (three types). The player starts with enough
materials for 3 to 4 towers.
- Creatures grant additional materials when destroyed.

## Map and Gameplay Mechanics
- Maps contain paths (one-way or two-way) and open zones where towers can be
placed.
- In open zones, the player can strategically place towers to increase path lengths for
creatures.
- If all paths to the resource are blocked, creatures ignore towers and continue
towards the resource.
