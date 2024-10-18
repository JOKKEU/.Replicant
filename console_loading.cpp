#include "console_loading.h"

namespace utils_thread
{
    std::mutex console_mutex;
    bool loading = true;
}

extern "C" void console_loading()
{
    utils_thread::loading = true;
    std::cout << "Loading";
    while (utils_thread::loading)
    {
        std::lock_guard<std::mutex> guard(utils_thread::console_mutex);
        for (size_t m = 0; m < 3; ++m)
        {
            std::cout << ".";
            std::cout.flush();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
    std::cout << "  \r\n";
}
