#ifndef __CONSOLE_LOADING_H__
#define __CONSOLE_LOADING_H__

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

namespace utils_thread
{
    extern std::mutex console_mutex;
    extern bool loading;
}

extern "C" void console_loading();

#endif 