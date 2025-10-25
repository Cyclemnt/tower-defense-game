#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include "../../include/waves/jsonWaveLoader.hpp"

JsonWaveLoader::JsonWaveLoader(const std::string& filename) {
    parseFile(filename);
}

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

void JsonWaveLoader::parseFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[JsonWaveLoader] Failed to open file: " << filename << std::endl;
        return;
    }

    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string json = buffer.str();
    trim(json);

    std::string timeline = extractArraySection(json, "timeline");
    auto waveObjects = splitObjects(timeline);

    for (const auto& text : waveObjects) {
        InternalWave w;
        w.waveNumber = extractIntValue(text, "wave");
        w.delay = extractIntValue(text, "start_delay_ms") * 0.001f;

        std::string groups = extractArraySection(text, "groups");
        auto groupObjects = splitObjects(groups);

        for (const auto& g : groupObjects) {
            CreatureType t = parseType(extractStringValue(g, "enemy"));
            int count = extractIntValue(g, "count");
            float interval = extractIntValue(g, "interval_ms") * 0.001f;

            for (int i = 0; i < count; ++i) {
                w.spawns.push_back({ t, interval });
            }
        }

        waves.push_back(std::move(w));
    }

    std::cout << "[JsonWaveLoader] Loaded " << waves.size() << " waves.\n";
}

bool JsonWaveLoader::hasMore() const {
    return index < waves.size();
}

WaveData JsonWaveLoader::next() {
    if (!hasMore()) return {};

    WaveData wave;
    const JsonWaveLoader::InternalWave& w = waves[index++];
    wave.spawns = w.spawns;
    wave.delay = w.delay;

    return wave;
}

CreatureType JsonWaveLoader::parseType(const std::string& n) const {
    if (n == "Minion") return CreatureType::Minion;
    if (n == "Drone")  return CreatureType::Drone;
    if (n == "Tank")   return CreatureType::Tank;
    if (n == "MinionB") return CreatureType::MinionB;
    if (n == "DroneB") return CreatureType::DroneB;
    if (n == "TankB")  return CreatureType::TankB;
    return CreatureType::Minion;
}
