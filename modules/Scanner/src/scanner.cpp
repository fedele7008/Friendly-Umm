#include "scanner.h"

using std::vector;
using std::string;
using std::ostream;
using std::map;
using scanner::Token;
using scanner::ScanningFailureException;

Token::Token(Token::Type type, string lexeme):
    type(type),
    lexeme(std::move(lexeme)) {}

Token::Type Token::getType() const {
    return type;
}

const string &Token::getLexeme() const {
    return lexeme;
}

scanner::ScanningFailureException::ScanningFailureException(const string &msg): msg("ScanningFailureException: " + msg) { }

const string &scanner::ScanningFailureException::what() const { return msg; }

ostream &scanner::operator<<(ostream &out, const Token &token)
{
    out << "Token: [";
    switch (token.getType()) {
        case Token::Type::SPACE: out << "SPACE"; break;
        case Token::Type::TAB: out << "TAB"; break;
        case Token::Type::NEWLINE: out << "NEWLINE"; break;
        case Token::Type::COMMENT: out << "COMMENT"; break;
        case Token::Type::BEGF: out << "BEGF"; break;
        case Token::Type::ENDF: out << "ENDF"; break;
        case Token::Type::NUM: out << "NUM"; break;
        case Token::Type::LPAREN: out << "LPAREN"; break;
        case Token::Type::RPAREN: out << "RPAREN"; break;
        case Token::Type::LBRACE: out << "LBRACE"; break;
        case Token::Type::RBRACE: out << "RBRACE"; break;
        case Token::Type::RETURN: out << "RETURN"; break;
        case Token::Type::IF: out << "IF"; break;
        case Token::Type::ELSE: out << "ELSE"; break;
        case Token::Type::WHILE: out << "WHILE"; break;
        case Token::Type::PRINT: out << "PRINT"; break;
        case Token::Type::PRINTLN: out << "PRINTLN"; break;
        case Token::Type::INPUT: out << "INPUT"; break;
        case Token::Type::MAIN: out << "MAIN"; break;
        case Token::Type::ASSIGN: out << "ASSIGN"; break;
        case Token::Type::INT: out << "INT"; break;
        case Token::Type::CHAR: out << "CHAR"; break;
        case Token::Type::EQ: out << "EQ"; break;
        case Token::Type::NE: out << "NE"; break;
        case Token::Type::PLUS: out << "PLUS"; break;
        case Token::Type::MINUS: out << "MINUS"; break;
        case Token::Type::STAR: out << "STAR"; break;
        case Token::Type::SLASH: out << "SLASH"; break;
        case Token::Type::COMMA: out << "COMMA"; break;
        case Token::Type::SEMI: out << "SEMI"; break;
        case Token::Type::LBRACK: out << "LBRACK"; break;
        case Token::Type::RBRACK: out << "RBRACK"; break;
        case Token::Type::STR: out << "STR"; break;
        case Token::Type::ID: out << "ID"; break;
        default: throw ScanningFailureException("<< Operator failed");
    }
    out << "] \'" << token.getLexeme() << "\'";
    return out;
}

class DFA {
    public:
    enum State {
        START = 0,
        FAIL,
        WHITESPACE,
        NEWLINE,
        ID,
        NUM,
        STR,
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
        CHAR_C,
        CHAR_H,
        CHAR_A,
        ELSE_E,
        ELSE_L,
        ELSE_S,
        PRE_I,
        INT_N,
        MAIN_M,
        MAIN_A,
        MAIN_I,
        PRINT_P,
        PRINT_R,
        PRINT_I,
        PRINT_N,
        PRINTLN_L,
        RETURN_R,
        RETURN_E,
        RETURN_T,
        RETURN_U,
        RETURN_R2,
        SCAN_S,
        SCAN_C,
        SCAN_A,
        WHILE_W,
        WHILE_H,
        WHILE_I,
        WHILE_L,
        COMMENT,
        NE_EX,
        STR_IN,
        LARGEST_STATE,
        ACCEPTING_STATES = 
        ID 
        | NUM 
        | STR 
        | LPAREN 
        | RPAREN 
        | LBRACE
        | RBRACE
        | RETURN
        | IF
        | ELSE 
        | WHILE 
        | PRINT 
        | PRINTLN 
        | INPUT
        | MAIN
        | ASSIGN
        | INT
        | CHAR
        | EQ
        | NE
        | PLUS
        | MINUS
        | STAR
        | SLASH
        | COMMA
        | SEMI
        | LBRACK
        | RBRACK
        | COMMENT
        | WHITESPACE
        | NEWLINE,
        SEMI_IDS = 
        CHAR_C
        | CHAR_H
        | CHAR_A
        | ELSE_E
        | ELSE_L
        | ELSE_S
        | PRE_I
        | INT_N
        | MAIN_M
        | MAIN_A
        | MAIN_I
        | PRINT_P
        | PRINT_R
        | PRINT_I
        | PRINT_N
        | PRINTLN_L
        | RETURN_R
        | RETURN_E
        | RETURN_T
        | RETURN_U
        | RETURN_R2
        | SCAN_S
        | SCAN_C
        | SCAN_A
        | WHILE_W
        | WHILE_H
        | WHILE_I
        | WHILE_L
        | COMMENT
        | NE_EX
        | STR_IN

    };

    private:

    Token::Type stateToKind(State state) const {
        switch(state) {
            case ID: return Token::Type::ID;
            case NUM: return Token::Type::NUM;
            case STR: return Token::Type::STR;
            case LPAREN: return Token::Type::LPAREN;
            case RPAREN: return Token::Type::RPAREN;
            case LBRACE: return Token::Type::LBRACE;
            case RBRACE: return Token::Type::RBRACE;
            case RETURN: return Token::Type::RETURN;
            case IF: return Token::Type::IF;
            case ELSE: return Token::Type::ELSE;
            case WHILE: return Token::Type::WHILE;
            case PRINT: return Token::Type::PRINT;
            case PRINTLN: return Token::Type::PRINTLN;
            case INPUT: return Token::Type::INPUT;
            case MAIN: return Token::Type::MAIN;
            case ASSIGN: return Token::Type::ASSIGN;
            case INT: return Token::Type::INT;
            case CHAR: return Token::Type::CHAR;
            case EQ: return Token::Type::EQ;
            case NE: return Token::Type::NE;
            case PLUS: return Token::Type::PLUS;
            case MINUS: return Token::Type::MINUS;
            case STAR: return Token::Type::STAR;
            case SLASH: return Token::Type::SLASH;
            case COMMA: return Token::Type::COMMA;
            case SEMI: return Token::Type::SEMI;
            case LBRACK: return Token::Type::LBRACK;
            case RBRACK: return Token::Type::RBRACK;
            case COMMENT: return Token::Type::COMMENT;
            case WHITESPACE: return Token::Type::SPACE;
            case NEWLINE: return Token::Type::NEWLINE;
            default: throw ScanningFailureException("Cannot convert State to Type: " + std::to_string(state));
        }
    }
    
    map<State, map<char, State>> transitions;

    void registerTransition(State oldState, const std::string &chars, State newState) {
        for (char c : chars) {
            transitions[oldState][c] = newState;
        }
    }

    public:
    DFA() {
        // Initialize all transitions
        for (int i = 0; i < State::LARGEST_STATE; i++) {
            for (size_t j = 0; j < 128; j++) {
                transitions[static_cast<State>(i)][j] = State::FAIL;
            }
        }

        // Register transitions
        registerTransition(State::START, "(", State::LPAREN);
        registerTransition(State::START, ")", State::RPAREN);
        registerTransition(State::START, "{", State::LBRACE);
        registerTransition(State::START, "}", State::RBRACE);
        registerTransition(State::START, "[", State::LBRACK);
        registerTransition(State::START, "]", State::RBRACK);
        registerTransition(State::START, ";", State::SEMI);
        registerTransition(State::START, ",", State::COMMA);
        registerTransition(State::START, "*", State::STAR);
        registerTransition(State::START, "+", State::PLUS);
        registerTransition(State::START, "-", State::MINUS);
        registerTransition(State::START, "0123456789", State::NUM);
        registerTransition(State::START, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", State::ID);
        registerTransition(State::NUM, "0123456789", State::NUM);
        registerTransition(State::ID, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::START, "=", State::ASSIGN);
        registerTransition(State::ASSIGN, "=", State::EQ);
        registerTransition(State::START, "!", State::NE_EX);
        registerTransition(State::NE_EX, "=", State::NE);
        registerTransition(State::START, "/", State::SLASH);
        registerTransition(State::SLASH, "/", State::COMMENT);
        registerTransition(State::COMMENT, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 !@\"#$%^&*()_-=+`~\\/?.>,<\':;|{}[]\t", State::COMMENT);
        registerTransition(State::START, "\"", State::STR_IN);
        registerTransition(State::STR_IN, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 !@#$%^&*()_-=+`~\\/?.>,<\':;|{}[]\t\n", State::STR_IN);
        registerTransition(State::STR_IN, "\"", State::STR);
        registerTransition(State::START, "c", State::CHAR_C);
        registerTransition(State::CHAR_C, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::CHAR_C, "h", State::CHAR_H);
        registerTransition(State::CHAR_H, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::CHAR_H, "a", State::CHAR_A);
        registerTransition(State::CHAR_A, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::CHAR_A, "r", State::CHAR);
        registerTransition(State::START, "e", State::ELSE_E);
        registerTransition(State::ELSE_E, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::ELSE_E, "l", State::ELSE_L);
        registerTransition(State::ELSE_L, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::ELSE_L, "s", State::ELSE_S);
        registerTransition(State::ELSE_S, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::ELSE_S, "e", State::ELSE);
        registerTransition(State::START, "i", State::PRE_I);
        registerTransition(State::PRE_I, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::PRE_I, "n", State::INT_N);
        registerTransition(State::PRE_I, "f", State::IF);
        registerTransition(State::INT_N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::INT_N, "t", State::INT);
        registerTransition(State::START, "m", State::MAIN_M);
        registerTransition(State::MAIN_M, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::MAIN_M, "a", State::MAIN_A);
        registerTransition(State::MAIN_A, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::MAIN_A, "i", State::MAIN_I);
        registerTransition(State::MAIN_I, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::MAIN_I, "n", State::MAIN);
        registerTransition(State::START, "p", State::PRINT_P);
        registerTransition(State::PRINT_P, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::PRINT_P, "r", State::PRINT_R);
        registerTransition(State::PRINT_R, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::PRINT_R, "i", State::PRINT_I);
        registerTransition(State::PRINT_I, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::PRINT_I, "n", State::PRINT_N);
        registerTransition(State::PRINT_N, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::PRINT_N, "t", State::PRINT);
        registerTransition(State::PRINT, "l", State::PRINTLN_L);
        registerTransition(State::PRINTLN_L, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::PRINTLN_L, "n", State::PRINTLN);
        registerTransition(State::START, "r", State::RETURN_R);
        registerTransition(State::RETURN_R, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::RETURN_R, "e", State::RETURN_E);
        registerTransition(State::RETURN_E, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::RETURN_E, "t", State::RETURN_T);
        registerTransition(State::RETURN_T, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::RETURN_T, "u", State::RETURN_U);
        registerTransition(State::RETURN_U, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::RETURN_U, "r", State::RETURN_R2);
        registerTransition(State::RETURN_R2, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::RETURN_R2, "n", State::RETURN);
        registerTransition(State::START, "s", State::SCAN_S);
        registerTransition(State::SCAN_S, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::SCAN_S, "c", State::SCAN_C);
        registerTransition(State::SCAN_C, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::SCAN_C, "a", State::SCAN_A);
        registerTransition(State::SCAN_A, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::SCAN_A, "n", State::INPUT);
        registerTransition(State::START, "w", State::WHILE_W);
        registerTransition(State::WHILE_W, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::WHILE_W, "h", State::WHILE_H);
        registerTransition(State::WHILE_H, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::WHILE_H, "i", State::WHILE_I);
        registerTransition(State::WHILE_I, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::WHILE_I, "l", State::WHILE_L);
        registerTransition(State::WHILE_L, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789", State::ID);
        registerTransition(State::WHILE_L, "e", State::WHILE);
        registerTransition(State::START, " \t", State::WHITESPACE);
        registerTransition(State::START, "\n", State::NEWLINE);
    }

    vector<Token> raw_tokenize(const string &input) const {
        vector<Token> result;

        State state = State::START;
        string munch = "";

        for (string::const_iterator it = input.begin(); it != input.end();) {
            State oldState = state;
            state = transitions.at(state).at(*it);

            // if ((oldState & State::SEMI_IDS) > 0 && state == State::FAIL)
            //     oldState = State::ID;

            if (state != State::FAIL) {
                munch += *it;
                oldState = state;
                ++it;
            }

            if (it == input.end() || state == State::FAIL) {
                if ((oldState & State::ACCEPTING_STATES) > 0) {
                    result.push_back(Token(stateToKind(oldState), munch));
                    munch = "";
                    state = State::START;
                } else {
                    if (state == State::FAIL) {
                        munch += *it;
                    }
                    throw ScanningFailureException("Something went wrong \"" + munch + "\"");
                }
            }
        }

        return result;
    }
};

vector<Token> scanner::scan(const string &input)
{
    static DFA dfa;
    vector<Token> tokens = dfa.raw_tokenize(input);

    for (size_t i = 0; i < tokens.size(); i++) {
        if ((tokens[i].getType() == Token::Type::SPACE)
        || (tokens[i].getType() == Token::Type::NEWLINE)
        || (tokens[i].getType() == Token::Type::TAB)
        || (tokens[i].getType() == Token::Type::COMMENT)) 
            tokens.erase(tokens.begin() + i--);
    }

    return tokens;
}
