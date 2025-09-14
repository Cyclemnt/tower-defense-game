#include "../include/pathfinder.hpp"
#include <unordered_map>
#include <queue>
#include <algorithm> // std::reverse

Pathfinder::Pathfinder(const Map& m)
    : map(m) {}

Pathfinder::~Pathfinder() {}

// Heuristic (can be changed if needed)
int Pathfinder::heuristic(Tile* a, Tile* b) const {
    // Manhattan distance (enough and light)
    return std::abs(a->getX() - b->getX()) + std::abs(a->getY() - b->getY());
}

// Find path from start tile to goal tile (using A* algorithm)
std::vector<Tile*> Pathfinder::findPath(Tile* start, Tile* goal) const {
    if (!start || !goal) return {};

    // Lambda comparator for priority queue
    auto cmp = [](Node* a, Node* b) { return a->fCost() > b->fCost(); };
    std::priority_queue<Node*, std::vector<Node*>, decltype(cmp)> openSet(cmp);

    std::unordered_map<Tile*, Node*> allNodes;

    // Init start node
    Node* startNode = new Node{start, 0, heuristic(start, goal), nullptr};
    openSet.push(startNode);
    allNodes[start] = startNode;

    std::vector<Tile*> path;

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        if (current->tile == goal) {
            // Reconstruct path
            Node* n = current;
            while (n) {
                path.push_back(n->tile);
                n = n->parent;
            }
            std::reverse(path.begin(), path.end());
            break;
        }

        for (Tile* neighbor : map.getNeighbors(current->tile)) {
            if (!neighbor->isWalkable()) continue;

            int newG = current->gCost + 1;
            if (allNodes.find(neighbor) == allNodes.end() || newG < allNodes[neighbor]->gCost) {
                Node* neighborNode = new Node{neighbor, newG, heuristic(neighbor, goal), current};
                allNodes[neighbor] = neighborNode;
                openSet.push(neighborNode);
            }
        }
    }

    // Clean up allocated nodes
    for (auto& [_, node] : allNodes) {
        delete node;
    }

    return path;
}