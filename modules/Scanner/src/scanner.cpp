#include "scanner.h"

#include <spdlog/spdlog.h>

scanner::Scanner::Scanner() {
    m_id = id_counter++;
    spdlog::trace("Scanner instantiated (id: {})", m_id);
}

scanner::Scanner::~Scanner() {
    spdlog::trace("Scanner destroyed (id: {})", m_id);
}

std::shared_ptr<scanner::Scanner> scanner::CreateScanner() {
    return std::make_shared<scanner::Scanner>();
}
