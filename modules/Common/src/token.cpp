#include "token.h"

#include <spdlog/spdlog.h>

#include <utility>

using std::string;
using common::Token;

Token::Token(string label, string lexeme)
        : label(std::move(label)), lexeme(std::move(lexeme)) {
    spdlog::trace("Token {} ({}) created.", this->label, this->lexeme);
}

Token::~Token() {
    spdlog::trace("Token {} ({}) destroyed.", label, lexeme);
}
