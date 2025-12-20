#ifndef FILE_MAP_SOURCE_HPP
#define FILE_MAP_SOURCE_HPP

#include <string>
#include "core/interfaces/iMapSource.hpp"

namespace tdg::infra {

    class FileMapSource final : public core::IMapSource {
    public:
        explicit FileMapSource(std::string folderPath);
        void setLevel(unsigned int level) override; // Sets the level of the map
        core::MapData loadMap() const override; // Loads the description of a map

    private:
        std::string m_folderPath; // Folder path to the txt files
        std::string m_filePath; // File path to the current txt file
    };

} // namespace tdg::infra

#endif // FILE_MAP_SOURCE_HPP
