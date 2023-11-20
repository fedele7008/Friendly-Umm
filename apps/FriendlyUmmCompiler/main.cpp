#include "scanner.h"

#include <spdlog/spdlog.h>

int main(int argc, char *argv[])
{
    spdlog::set_level(spdlog::level::trace);
    auto scanner = scanner::CreateScanner();
}
