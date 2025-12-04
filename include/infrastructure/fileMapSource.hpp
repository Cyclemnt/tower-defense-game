#ifndef FILE_MAP_SOURCE_HPP
#define FILE_MAP_SOURCE_HPP

#include "core/interfaces/iMapSource.hpp"
#include "core/map.hpp"
#include <string>

namespace tdg::infra {

    class FileMapSource : public core::IMapSource {
    public:
        explicit FileMapSource(std::string folderPath);
        core::MapData loadMap(unsigned int level) const override;

    private:
        std::string m_folderPath;
    };

} // namespace tdg::infra

#endif // FILE_MAP_SOURCE_HPP
