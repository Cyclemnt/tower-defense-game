#include "jsonWaveLoader.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

JsonWaveLoader::JsonWaveLoader(const std::string& filename) {
    loadJsonFile(filename);
}

// --- petits helpers internes ---
namespace {
    inline void trim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            [](unsigned char c) { return !std::isspace(c); }));
        s.erase(std::find_if(s.rbegin(), s.rend(),
            [](unsigned char c) { return !std::isspace(c); }).base(), s.end());
    }

    inline std::string extractStringValue(const std::string& src, const std::string& key) {
        // Cherche "key": "value"
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
        // Cherche "key": nombre
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
        // Cherche "key": [ ... ]
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
        // Découpe le contenu d’un tableau [ {..}, {..}, ... ]
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

void JsonWaveLoader::loadJsonFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[JsonWaveLoader] Failed to open file: " << filename << std::endl;
        return;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string jsonText = buffer.str();
    trim(jsonText);

    // Trouver la section "timeline"
    std::string timelineSection = extractArraySection(jsonText, "timeline");
    if (timelineSection.empty()) {
        std::cerr << "[JsonWaveLoader] No timeline section found\n";
        return;
    }

    // Découper chaque wave { ... }
    auto waveObjects = splitObjects(timelineSection);
    for (const auto& waveText : waveObjects) {
        WaveData wave;
        wave.waveNumber   = extractIntValue(waveText, "wave");
        wave.startDelayMs = extractIntValue(waveText, "start_delay_ms");

        std::string groupsSection = extractArraySection(waveText, "groups");
        if (!groupsSection.empty()) {
            auto groupObjects = splitObjects(groupsSection);
            for (const auto& groupText : groupObjects) {
                WaveGroup group;
                group.type       = parseCreatureType(extractStringValue(groupText, "enemy"));
                group.count      = extractIntValue(groupText, "count");
                group.intervalMs = extractIntValue(groupText, "interval_ms");
                wave.groups.push_back(group);
            }
        }
        timeline.push_back(std::move(wave));
    }

    std::cout << "[JsonWaveLoader] Loaded " << timeline.size() << " waves from " << filename << std::endl;
}

CreatureType JsonWaveLoader::parseCreatureType(const std::string& name) const {
    if (name == "Minion") return CreatureType::Minion;
    if (name == "Drone")  return CreatureType::Drone;
    if (name == "Tank")   return CreatureType::Tank;
    return CreatureType::Minion;
}

bool JsonWaveLoader::hasNextWave() const {
    return currentWaveIndex < timeline.size();
}

std::vector<JsonWaveLoader::WaveEntry> JsonWaveLoader::getNextWave() {
    if (!hasNextWave()) return {};

    const WaveData& wave = timeline[currentWaveIndex++];
    std::vector<WaveEntry> entries;

    for (const auto& group : wave.groups)
        entries.push_back({ group.type, group.count });

    return entries;
}
