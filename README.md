# Tower Defense Game
A simplified tower defense game in C++.

## Overview
This project is an educational implementation of a tower defense game.  
It is designed with an **object-oriented approach** in C++ and follows principles of clean architecture (SOLID).  

The codebase is modular and aims to separate the following concerns:
- **Map management** (tiles, entry zones, exit zones, core storage).
- **Pathfinding** (finding shortest paths for creatures).
- **Game entities** (creatures, towers, resources).
- **Game loop** (spawning, updating, interactions between entities).

The project currently runs in **console mode** for debugging and testing purposes.  
Later iterations may use **SFML** and **TGUI** for rendering and UI.

---

## Game Concept
- The game is played on a **grid-based, top-down map**.
- A limited number of **cores** (the resource to defend) are stored in a special tile.
- **Creatures** spawn from entry zones and attempt to reach the core storage using the shortest path.
- If a creature reaches the core storage:
  - It steals one core.
  - It then tries to reach an exit zone, again following the shortest path.
- If a creature carrying a core is destroyed:
  - The core returns to the base.
- If the creature exits the map with the core:
  - The core is lost permanently.
- **Towers** can be built by the player to defend the base:
  - Different tower types exist (e.g., Gun, Laser, Inferno).
  - Towers have stats such as damage, range, fire rate, and whether they deal area damage.
  - Towers can be upgraded to higher levels.
- Towers cost **materials** to build:
  - Three types exist: Au (gold), Ag (silver), Cu (copper).
  - The player starts with a limited stock (enough for 3–4 towers).
  - Defeating creatures grants additional materials.

---

## Map and Gameplay Mechanics
- The map is made of different **tiles**:
  - `Path` tiles: walkable by creatures.
  - `OpenZone` tiles: buildable areas for towers.
  - `EntryZone` tiles: where creatures spawn.
  - `ExitZone` tiles: where creatures attempt to escape.
  - `CoreStorage` tile: where the cores are initially stored.
  - `EmptyZone` tiles: neutral/unusable areas.
- Creatures always search for the **shortest available path**.
- The player can **strategically place towers** to lengthen enemy paths and maximize damage dealt.
- If all paths to the resource are blocked:
  - Creatures will still attempt to reach the resource using the last known path.
  - Towers cannot permanently prevent access to the cores.

---

## Technical Details
- **Language**: C++17  
- **Build System**: CMake  
- **Core libraries**: STL (no external dependencies at this stage)  
- **Future libraries**: [SFML](https://www.sfml-dev.org/) for graphics, [TGUI](https://tgui.eu/) for UI  

### Key Components
- `Tile` and its subclasses (`Path`, `OpenZone`, `EntryZone`, `ExitZone`, `CoreStorage`, `EmptyZone`).
- `Map`: manages the grid and stores references to special zones.
- `Pathfinder`: implements A* to compute shortest paths.
- `Creature`: represents an enemy (HP, shield, speed, cores carried).
- `Tower`: represents a defense structure (stats, upgrade system, attack logic).
- `Game`: the main loop, spawns enemies, updates entities, and checks win/lose conditions.

---

## Current Status
- **UML draft** designed and partially implemented.  
- Base class structure created (`Tile`, `Map`, `Creature`, `Tower`).  
- Pathfinding algorithm (A*) implemented and tested on sample maps.  
- Work in progress: completing tower types, defining game loop, resource management.  

---

## Contributors
- Clément Lamouller
- Luan Parizot