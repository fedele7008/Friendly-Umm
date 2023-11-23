#include "token.h"

#include <gtest/gtest.h>
#include <spdlog/spdlog.h>

TEST(SampleTest, Test1) {
    spdlog::set_level(spdlog::level::trace);
    auto scanner = std::make_shared<common::Token>("T", "test");
}
