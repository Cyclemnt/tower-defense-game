#ifndef CORE_STORAGE_HPP
#define CORE_STORAGE_HPP

#include <vector>

namespace tdg::core {

    class CoreStorage {
    public:
        explicit CoreStorage(unsigned int count);

        unsigned int total() const noexcept;
        unsigned int safeCount() const noexcept { return m_safe; }
        unsigned int stolenCount() const noexcept { return m_stolen; }
        unsigned int lostCount() const noexcept { return m_lost; }

        unsigned int take(unsigned int n);
        void give(unsigned int n);
        void loose(unsigned int n);

        bool allLost() const noexcept;

    private:
        unsigned int m_safe;
        unsigned int m_stolen;
        unsigned int m_lost;
    };

} // namespace tdg::core

#endif // CORE_STORAGE_HPP