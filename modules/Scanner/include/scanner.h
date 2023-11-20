#ifndef FEDELE7008_SCANNER_SCANNER_H
#define FEDELE7008_SCANNER_SCANNER_H

#include <memory>

namespace scanner {

    class Scanner {
    private:
        uint32_t id_counter;
        uint32_t m_id;
    public:
        Scanner();
        virtual ~Scanner();
    };

    std::shared_ptr<Scanner> CreateScanner();
}

#endif