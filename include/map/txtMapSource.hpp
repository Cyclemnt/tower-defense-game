#ifndef TXT_MAP_SOURCE_HPP
#define TXT_MAP_SOURCE_HPP

#include <string>
#include "iMapSource.hpp"

class TxtMapSource : public IMapSource {
private:
    std::string filename;

public:
    explicit TxtMapSource(std::string path);
    void buildMap(Map& map, Cores* cores) override;
};

#endif // TXT_MAP_SOURCE_HPP
