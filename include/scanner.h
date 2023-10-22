#ifndef __SCANNER_H__
#define __SCANNER_H__

#include <iostream>
#include <string>
#include <algorithm>
#include <utility>
#include <map>
#include <vector>

namespace scanner {
    using std::vector;
    using std::string;
    using std::ostream;

    class Token;

    vector<Token> scan(const string &input);
    ostream &operator<<(ostream &out, const Token &token);

    class Token {
        public:
        enum Type {
            SPACE = 0,
            TAB,
            NEWLINE,
            COMMENT,
            BEGF,
            ENDF,
            ID,
            NUM,
            LPAREN,
            RPAREN,
            LBRACE,
            RBRACE,
            RETURN,
            IF,
            ELSE,
            WHILE,
            PRINT,
            PRINTLN,
            INPUT,
            MAIN,
            ASSIGN,
            INT,
            CHAR,
            EQ,
            NE,
            PLUS,
            MINUS,
            STAR,
            SLASH,
            COMMA,
            SEMI,
            LBRACK,
            RBRACK,
            STR,
        };

        private:
        Type type;
        string lexeme;

        public:
        Token(Type type, string lexeme);

        Type getType() const;
        const string &getLexeme() const;
    };

    class ScanningFailureException {
        string msg;

        public:
        ScanningFailureException(const string &msg);

        const string &what() const;
    };
}

#endif