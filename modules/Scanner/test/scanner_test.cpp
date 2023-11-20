#include "scanner.h"

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

namespace
{
    TEST(ScannerTest, CreateInstance)
    {
        spdlog::set_level(spdlog::level::trace);
        auto scanner = scanner::CreateScanner();
    }
}
