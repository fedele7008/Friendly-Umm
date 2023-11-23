#include "scanner.h"

#include <spdlog/spdlog.h>

using scanner::Scanner;

Scanner::Scanner() {
    spdlog::trace("Scanner created");
}

Scanner::~Scanner() {
    spdlog::trace("Scanner destroyed");
}

Scanner *scanner::CreateScanner() {
    return new Scanner();
}
