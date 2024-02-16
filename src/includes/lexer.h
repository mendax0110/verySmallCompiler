#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <memory>
#include <unordered_set>
#include <assert.h>
#include "../includes/tokenizer.h"

using namespace tokenInternals;

/// @brief Namespace for the lexer internals \namespace lexerInternals
namespace lexerInternals
{
    /// @brief Class for the lexer \class Lexer
    class Lexer
    {
    public:
        Lexer(std::string src);
        ~Lexer();
        void nextChar(void);
        char peek(void) const;
        void abort(std::string message);
        void skipWhitespace(void);
        void skipComment(void);
        Token getToken(void);
        char getCurChar(void) const;
        bool isEOF(const Token &token) const;
        void lexRecursively(void);

    private:
        std::string source;
        char curChar;
        int curPos;   
        int sourceLen;
        bool checkIsKeyword(const Token &token);
    };
}
#endif // LEXER_H