#ifndef FILE_MAP_SOURCE_HPP
#define FILE_MAP_SOURCE_HPP

#include "core/interfaces/iMapSource.hpp"
#include "core/map.hpp"
#include <string>

namespace tdg::infra {

    class FileMapSource : public core::IMapSource {
    public:
        explicit FileMapSource(std::string folderPath);
        void setLevel(unsigned int level) override;
        core::MapData loadMap() const override;

    private:
        std::string m_folderPath;
        std::string m_filePath;
    };

} // namespace tdg::infra

#endif // FILE_MAP_SOURCE_HPP
