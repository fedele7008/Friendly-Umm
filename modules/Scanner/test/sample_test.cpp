#include "scanner.h"

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

namespace
{
    TEST(SampleTest, Test1)
    {
        spdlog::set_level(spdlog::level::off);
        EXPECT_EQ(1, 1);
    }
}