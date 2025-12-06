#ifndef JSON_WAVE_SOURCE_HPP
#define JSON_WAVE_SOURCE_HPP

#include <string>
#include "core/interfaces/iWaveSource.hpp"

namespace tdg::infra {

    class JsonWaveSource : public core::IWaveSource {
    public:
        explicit JsonWaveSource(std::string folderPath);

        unsigned int waveCount() const override { return m_waveCount; }
        void setLevel(unsigned int level) override;
        core::WaveData loadWave(unsigned int waveIndex) const override;

    private:
        std::string m_folderPath;
        std::string m_filePath;
        unsigned int m_waveCount{0};

        std::vector<core::WaveData> waves;

        core::Creature::Type parseType(const std::string& n) const noexcept;
    };

} // namespace tdg::infra

#endif // JSON_WAVE_SOURCE_HPP