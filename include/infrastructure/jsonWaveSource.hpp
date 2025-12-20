#ifndef JSON_WAVE_SOURCE_HPP
#define JSON_WAVE_SOURCE_HPP

#include <string>
#include "core/interfaces/iWaveSource.hpp"

namespace tdg::infra {

    class JsonWaveSource final : public core::IWaveSource {
    public:
        explicit JsonWaveSource(std::string folderPath);

        unsigned int waveCount() const override { return m_waveCount; } // To get the number of waves
        void setLevel(unsigned int level) override; // To set the level of the waves
        core::WaveData loadWave(unsigned int waveIndex) const override; // To load the description of a wave

    private:
        std::string m_folderPath; // Folder path to the json
        std::string m_filePath; // File path to the current json
        unsigned int m_waveCount{0}; // Number of waves in the level

        core::Creature::Type parseType(const std::string& n) const noexcept; // Converts string to creature Type
    };

} // namespace tdg::infra

#endif // JSON_WAVE_SOURCE_HPP