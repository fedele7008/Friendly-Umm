#ifndef FEDELE7008_SCANNER_SCANNER_H
#define FEDELE7008_SCANNER_SCANNER_H

namespace scanner {
    class Scanner {
    public:
        Scanner();
        virtual ~Scanner();
    };

    Scanner *CreateScanner();
}

#endif