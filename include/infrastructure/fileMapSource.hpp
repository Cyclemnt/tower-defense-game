#ifndef FILE_MAP_SOURCE_HPP
#define FILE_MAP_SOURCE_HPP

#include <string>
#include "core/interfaces/iMapSource.hpp"

namespace tdg::infra {

    class FileMapSource final : public core::IMapSource {
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
