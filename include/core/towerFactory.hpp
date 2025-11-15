#ifndef TOWER_FACTORY_HPP
#define TOWER_FACTORY_HPP

#include "tower.hpp"
#include <functional>
#include <unordered_map>
#include <string>

namespace tdg::core {

    class TowerFactory {
    public:
        using Creator = std::function<TowerPtr(int, int)>;

        static TowerFactory& instance();

        void registerType(const std::string& id, Creator creator);
        TowerPtr create(const std::string& id, int x, int y) const;
        bool hasType(const std::string& id) const;

    private:
        TowerFactory() = default;
        std::unordered_map<std::string, Creator> m_creators;
    };

} // namespace tdg::core

#endif // TOWER_FACTORY_HPP