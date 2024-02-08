#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <memory>
#include <unordered_set>
#include <assert.h>
#include "../includes/tokenizer.h"

using namespace tokenInternals;

namespace lexerInternals
{
    class Lexer
    {
    public:
        Lexer(std::string src);
        void nextChar(void);
        char peek(void) const;
        void abort(std::string message);
        void skipWhitespace(void);
        void skipComment(void);
        Token getToken(void);
        char getCurChar(void) const;
        bool isEOF(const Token &token) const;

    private:
        std::string source;
        char curChar;
        int curPos;   
        int sourceLen;
        bool checkIsKeyword(const Token &token);
    };
}
#endif // LEXER_H