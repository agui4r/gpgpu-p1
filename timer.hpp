#include <chrono>
#include <stdio.h>

class Timer {
public:
    Timer(const char *format)
        : m_format(format)
    {
        m_start = std::chrono::system_clock::now();
    }

    ~Timer()
    {
        auto end = std::chrono::system_clock::now();
        auto elapsed = static_cast<double>(std::chrono::duration_cast<std::chrono::microseconds>(end - m_start).count()) / 1000.0;
        printf(m_format, elapsed);
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_start;
    const char *m_format;
};

