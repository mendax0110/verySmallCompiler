#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <memory>
#include <cassert>
#include "../includes/emitter.h"
#include "../includes/tokenizer.h"
#include "../includes/lexer.h"

using namespace lexerInternals;
using namespace tokenInternals;
using namespace emitterInternals;

namespace parserInternals
{
    class Parser
    {
    public:
        Parser(const std::string& source);
        ~Parser();
        bool checkToken(TokenType t);
        bool checkPeek(TokenType t);
        bool match(TokenType t);
        void nextToken();
        void emitIndentation();
        void abort(const std::string& message);
        void program();
        void end(const std::string& output);

        void isPass();
        void isInput();
        void isLet();
        void isWhile();
        void isIf();
        void isPrint();
        
    private:
        Token currentToken;
        Token peekToken;
        int indent_count;
        std::shared_ptr<Lexer> _lexer;
        std::shared_ptr<Emitter> _emitter;

        bool isCompareOps();
        void statement();
        void expression();
        void newLine();
        void comparison();
        void term();
        void unary();
        void primary();
        void endOfFile();
        void debug();
    };
}

#endif // PARSER_H