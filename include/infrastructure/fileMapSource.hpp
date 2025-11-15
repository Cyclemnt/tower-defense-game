#ifndef FILE_MAP_SOURCE_HPP
#define FILE_MAP_SOURCE_HPP

#include "core/interfaces/iMapSource.hpp"
#include "core/map.hpp"
#include <string>

namespace tdg::infra {

    class FileMapSource : public core::IMapSource {
    public:
        explicit FileMapSource(std::string path);
        core::MapData loadMap(const std::string& mapId) const override;

    private:
        std::string m_path;
    };

} // namespace tdg::infra

#endif // FILE_MAP_SOURCE_HPP