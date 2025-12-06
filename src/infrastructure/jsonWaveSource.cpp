#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "infrastructure/jsonWaveSource.hpp"

// Forward declaration, see later in this file
namespace {
    inline void trim(std::string& s);
    inline std::string extractStringValue(const std::string& src, const std::string& key);
    inline int extractIntValue(const std::string& src, const std::string& key);
    inline std::string extractArraySection(const std::string& src, const std::string& key);
    inline std::vector<std::string> splitObjects(const std::string& arrContent);
}

namespace tdg::infra {
    
    JsonWaveSource::JsonWaveSource(std::string folderPath)
        : m_folderPath(folderPath)
    {
        setLevel(1u);
    }

    void JsonWaveSource::setLevel(unsigned int level) {
        m_filePath = m_folderPath + "level" + std::to_string(level) + ".json";

        // Open JSON file to count waves
        std::ifstream file(m_filePath);
        if (!file.is_open()) {
            std::cerr << "[JsonWaveSource] Failed to open file: " << m_filePath << std::endl;
            return;
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        std::string json = buffer.str();
        trim(json);

        file.close();

        // Count objects in "timeline"
        std::string timeline = extractArraySection(json, "timeline");
        auto waveObjects = splitObjects(timeline);

        m_waveCount = waveObjects.size();
    }

    core::WaveData JsonWaveSource::loadWave(unsigned int waveIndex) const {
        std::ifstream file(m_filePath);
        if (!file.is_open()) {
            std::cerr << "[JsonWaveSource] Failed to open file: " << m_filePath << std::endl;
            return {0.0f, {}};
        }

        std::ostringstream buffer;
        buffer << file.rdbuf();
        std::string json = buffer.str();
        trim(json);

        file.close();

        std::string timeline = extractArraySection(json, "timeline");
        auto waveObjects = splitObjects(timeline);

        // Scan waves until finding the one matching waveIndex
        for (const std::string& text : waveObjects) {
            // If it's the wave we search for
            if (extractIntValue(text, "wave") == waveIndex) {
                core::WaveData w;
                w.startDelay = extractIntValue(text, "start_delay_ms") * 0.001f;

                std::string groups = extractArraySection(text, "groups");
                std::vector<std::string> groupObjects = splitObjects(groups);

                for (const std::string& g : groupObjects) {
                    core::Creature::Type type = parseType(extractStringValue(g, "enemy"));
                    int count = extractIntValue(g, "count");
                    int entrance = extractIntValue(g, "entrance");
                    float interval = extractIntValue(g, "interval_ms") * 0.001f;

                    for (int i = 0; i < count; ++i) {
                        core::SpawnEntry se = {interval, entrance, type};
                        w.spawns.push_back(se);
                    }
                }

                return w;
            }
        }
        return {0.0f, {}};
    }

    core::Creature::Type JsonWaveSource::parseType(const std::string& n) const noexcept {
        if      (n == "Minion")  return core::Creature::Type::Minion;
        else if (n == "Drone")   return core::Creature::Type::Drone;
        else if (n == "Tank")    return core::Creature::Type::Tank;
        else if (n == "MinionB") return core::Creature::Type::MinionB;
        else if (n == "DroneB")  return core::Creature::Type::DroneB;
        else if (n == "TankB")   return core::Creature::Type::TankB;
        else return core::Creature::Type::Minion;
    }

} // namespace tdg::infra

// Helpers
namespace {
    inline void trim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            [](unsigned char c) { return !std::isspace(c); }));
        s.erase(std::find_if(s.rbegin(), s.rend(),
            [](unsigned char c) { return !std::isspace(c); }).base(), s.end());
    }

    inline std::string extractStringValue(const std::string& src, const std::string& key) {
        // Search "key": "value"
        size_t pos = src.find("\"" + key + "\"");
        if (pos == std::string::npos) return "";
        pos = src.find(':', pos);
        if (pos == std::string::npos) return "";
        pos = src.find('"', pos);
        if (pos == std::string::npos) return "";
        size_t end = src.find('"', pos + 1);
        if (end == std::string::npos) return "";
        return src.substr(pos + 1, end - pos - 1);
    }

    inline int extractIntValue(const std::string& src, const std::string& key) {
        // Search "key": number
        size_t pos = src.find("\"" + key + "\"");
        if (pos == std::string::npos) return 0;
        pos = src.find(':', pos);
        if (pos == std::string::npos) return 0;
        size_t start = src.find_first_of("-0123456789", pos);
        if (start == std::string::npos) return 0;
        size_t end = src.find_first_not_of("0123456789", start + 1);
        return std::stoi(src.substr(start, end - start));
    }

    inline std::string extractArraySection(const std::string& src, const std::string& key) {
        // Search "key": [ ... ]
        size_t pos = src.find("\"" + key + "\"");
        if (pos == std::string::npos) return "";
        pos = src.find('[', pos);
        if (pos == std::string::npos) return "";
        int depth = 1;
        size_t i = pos + 1;
        while (i < src.size() && depth > 0) {
            if (src[i] == '[') depth++;
            else if (src[i] == ']') depth--;
            i++;
        }
        if (depth != 0) return "";
        return src.substr(pos + 1, i - pos - 2);
    }

    inline std::vector<std::string> splitObjects(const std::string& arrContent) {
        // Split an array [ {..}, {..}, ... ]
        std::vector<std::string> objects;
        size_t pos = 0;
        while (pos < arrContent.size()) {
            size_t start = arrContent.find('{', pos);
            if (start == std::string::npos) break;
            int depth = 1;
            size_t i = start + 1;
            while (i < arrContent.size() && depth > 0) {
                if (arrContent[i] == '{') depth++;
                else if (arrContent[i] == '}') depth--;
                i++;
            }
            if (depth == 0)
                objects.push_back(arrContent.substr(start, i - start));
            pos = i;
        }
        return objects;
    }
}
