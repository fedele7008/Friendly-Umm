#ifndef FEDELE7008_COMMON_TOKEN_H
#define FEDELE7008_COMMON_TOKEN_H

#include <string>

namespace common {

    using std::string;

    class Token {
    public:
        Token(string label, string lexeme);
        virtual ~Token();
    private:
        string label;
        string lexeme;
    };
}

#endif // FEDELE7008_COMMON_TOKEN_H
