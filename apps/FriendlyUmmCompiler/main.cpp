#include "scanner.h"

#include <spdlog/spdlog.h>
#include <memory>

int main(int argc, char *argv[])
{
    spdlog::set_level(spdlog::level::trace);
    auto scanner = std::shared_ptr<scanner::Scanner>(scanner::CreateScanner());
}
