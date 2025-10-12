#include <queue>
#include <algorithm> // std::reverse
#include <unordered_map>
#include "../include/pathfinder.hpp"
#include "../include/map/tile.hpp"

Pathfinder::Pathfinder(const Map& m)
    : map(m) {}

Pathfinder::~Pathfinder() {}

int Pathfinder::heuristic(Tile* a, Tile* b) const {
    // Manhattan distance: sum of absolute differences between x and y coordinates.
    // Useful for grids with only horizontal/vertical movement (no diagonal).
    return std::abs(a->getX() - b->getX()) + std::abs(a->getY() - b->getY());
}

std::vector<Tile*> Pathfinder::findPath(Tile* start, Tile* goal, bool ignoreTowers) const {
    if (!start || !goal) return {};  // Return an empty path if start or goal are invalid.

    // Comparator for the priority queue, sorts nodes by their total cost (fCost = gCost + hCost).
    auto cmp = [](Node* a, Node* b) { return a->fCost() > b->fCost(); };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> openSet(cmp);  // Priority queue for nodes to explore.

    std::unordered_map<Tile*, Node*> allNodes;  // Map to keep track of all explored nodes.

    // Initialize the start node: gCost = 0, hCost calculated using the heuristic function.
    Node* startNode = new Node{start, 0, heuristic(start, goal), nullptr};
    openSet.push(startNode);  // Add the start node to the priority queue.
    allNodes[start] = startNode;  // Record the start node in allNodes for fast access.

    std::vector<Tile*> path;  // The final path to return.

    while (!openSet.empty()) {
        Node* current = openSet.top();  // Get the node with the lowest total cost (fCost).
        openSet.pop();  // Remove it from the priority queue.

        // If we reach the goal, reconstruct the path.
        if (current->tile == goal) {
            Node* n = current;
            while (n) {  // Trace back through the parent nodes to reconstruct the path.
                path.push_back(n->tile);  // Add the current tile to the path.
                n = n->parent;  // Move to the parent node.
            }
            std::reverse(path.begin(), path.end());  // Reverse the path to get it from start to goal.
            break;  // Exit the loop once the path is found.
        }

        // Explore the neighbors of the current node.
        for (Tile* neighbor : map.getNeighbors(current->tile)) {
            // If the neighbor is not walkable, skip it.
            // Or, if ignoreTowers == true, accept OpenZones regardless of occupation.
            if (!(neighbor->isWalkable() || (ignoreTowers && neighbor->getTypeName() == "OpenZone"))) continue;

            // Calculate the new gCost for this neighbor (gCost of the parent + 1 for the move).
            int newG = current->gCost + 1;

            // If this neighbor hasn't been explored or if we found a shorter path:
            if (allNodes.find(neighbor) == allNodes.end() || newG < allNodes[neighbor]->gCost) {
                // Create a new node for the neighbor with updated gCost and the current node as the parent.
                Node* neighborNode = new Node{neighbor, newG, heuristic(neighbor, goal), current};
                allNodes[neighbor] = neighborNode;  // Add the neighbor to the allNodes map.
                openSet.push(neighborNode);  // Add the neighbor to the priority queue to explore.
            }
        }
    }

    // Clean up the dynamically allocated nodes.
    for (auto& [_, node] : allNodes) {
        delete node;
    }

    // Return the found path (or an empty path if none was found).
    return path;
    // TODO: if no path found, search again with walkable OR occupied tiles
}