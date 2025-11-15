#ifndef JSON_WAVE_SOURCE_HPP
#define JSON_WAVE_SOURCE_HPP

#include "core/interfaces/iWaveSource.hpp"
#include <string>

namespace tdg::infra {

    class JsonWaveSource : public core::IWaveSource {
    public:
        explicit JsonWaveSource(std::string path);
        std::vector<tdg::core::WaveData> getWaves() const override;

    private:
        std::string m_path;
    };

} // namespace tdg::infra

#endif // JSON_WAVE_SOURCE_HPP