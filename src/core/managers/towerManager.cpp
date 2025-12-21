#include "core/managers/towerManager.hpp"
#include "core/factories/towerFactory.hpp"

#include "core/events.hpp"
#include "core/map.hpp"
#include "core/player.hpp"

namespace tdg::core {

    TowerManager::TowerManager(Map& map, Player& player, const std::vector<CreaturePtr>& creatures)
        : m_map(map), m_player(player), m_creatures(creatures) {}

    void TowerManager::update(float dt, Events& events) {
        for (TowerPtr& tower : m_towers) tower->update(dt, events, m_creatures);
    }

    bool TowerManager::buildTower(Tower::Type type, int x, int y) {
        if (!m_map.canRecieveTowerAt(x, y)) return false;

        // Build the tower
        TowerPtr newTower = m_factory.create(type, x, y);
        if (!newTower) return false;

        // If player can afford,
        if (!m_player.canAfford(newTower->cost())) return false;

        // Pay the tower
        m_player.buy(newTower->cost());

        // Mark the tile
        m_map.markTowerAt(x, y);

        // Sorted Insertion
        auto it = std::upper_bound(m_towers.begin(), m_towers.end(), newTower,
            [](const TowerPtr& a, const TowerPtr& b) { return a->y() < b->y(); });
        m_towers.insert(it, std::move(newTower));

        return true;
    }

    bool TowerManager::upgradeTower(int x, int y) {
        if (!m_map.hasTowerAt(x, y)) return false;

        for (auto it = m_towers.begin(); it != m_towers.end(); ++it) {
            TowerPtr& tower = *it;

            if (tower->x() == x && tower->y() == y) {
                // If player can afford,
                if (!m_player.canAfford(tower->upgradeCost())) return false;
                // Pay the upgrade
                m_player.buy(tower->upgradeCost());
                // Then upgrade
                tower->upgrade();

                return true;
            }
        }
        return false;
    }

    bool TowerManager::sellTower(int x, int y) {
        if (!m_map.hasTowerAt(x, y)) return false;

        for (auto it = m_towers.begin(); it != m_towers.end(); ++it) {
            TowerPtr& tower = *it;

            if (tower->x() == x && tower->y() == y) {
                // Give player the sell value of the tower
                m_player.addMaterials(tower->sellValue());
                // Erease the tower
                m_map.removeTowerAt(x, y);
                m_towers.erase(it);

                return true;
            }
        }
        return false;
    }

    std::optional<float> TowerManager::towerRangeAt(int x, int y) const {
        if (!m_map.hasTowerAt(x, y)) return std::nullopt;
        for (auto it = m_towers.begin(); it != m_towers.end(); ++it) {
            const TowerPtr& t = *it;
            if (t->x() == x && t->y() == y) {
                return t->stats().range;
            }
        }
        return std::nullopt;
    }

} // namespace tdg::core
