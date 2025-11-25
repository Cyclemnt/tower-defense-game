#include "core/coreStorage.hpp"
#include <cmath>

namespace tdg::core {

    CoreStorage::CoreStorage(unsigned int initialAmount)
        : m_safe(initialAmount) {}

    unsigned int CoreStorage::total() const noexcept { return m_safe + m_stolen + m_lost; }

    unsigned int CoreStorage::stealCores(unsigned int n) {
        const unsigned int taken = std::min(n, m_safe);
        m_safe   -= taken;
        m_stolen += taken;
        return taken;
    }

    void CoreStorage::returnCores(unsigned int n) {
        if (n > m_stolen) n = m_stolen;
        m_stolen -= n;
        m_safe   += n;
    }

    void CoreStorage::loseCores(unsigned int n) {
        if (n > m_stolen) n = m_stolen;
        m_stolen -= n;
        m_lost   += n;
    }

    bool CoreStorage::allLost() const noexcept {
        return m_safe == 0 && m_stolen == 0;
    }

} // namespace tdg::core