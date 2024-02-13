#include "../src/includes/lexer.h"
#include "../src/includes/tokenizer.h"
#include <cctype>

using namespace lexerInternals;
using namespace tokenInternals;
using namespace std;

Lexer::Lexer(string src)
    : source(src + "\n"), curChar(0), curPos(-1), sourceLen(source.length())
{
}

Lexer::~Lexer()
{
    cout << "-----------------------\n";
    cout << "Lexer Object destroyed.\n";
    cout << "-----------------------\n";
}

void Lexer::nextChar()
{
    curPos += 1;
    curChar = (curPos >= sourceLen) ? '\0' : source[curPos];
}

char Lexer::peek() const
{
    return (curPos + 1 >= sourceLen) ? '\0' : source[curPos + 1];
}

bool Lexer::isEOF(const Token &token) const
{
    return (token.type == _EOF);
}

void Lexer::skipWhitespace()
{
    while (isspace(curChar))
    {
        nextChar();
    }
}

void Lexer::skipComment()
{
    if (curChar == '#')
    {
        while (curChar != '\n')
        {
            nextChar();
        }
    }
}

void Lexer::abort(string message)
{
    cout << "Error: " + message + "\n";
    assert(0==1);
}

Token Lexer::getToken()
{
    nextChar();
    skipComment();
    skipWhitespace();
    string text;
    size_t startPos;

    switch (curChar)
    {
    case '+':
        return Token(PLUS);
    case '-':
        return Token(MINUS);
    case '*':
        return Token(ASTERISK);
    case '/':
        return Token(SLASH);
    case '\n':
        return Token(NEWLINE);
    case '\0':
        return Token(_EOF);
    case '=':
        return (peek() == '=') ? (nextChar(), Token(EQEQ)) : Token(EQ);
    case '!':
        return (peek() == '=') ? (nextChar(), Token(NOTEQ)) : (abort("not supported\n"), Token(UNKNOWN));
    case '<':
        return (peek() == '=') ? (nextChar(), Token(LTEQ)) : Token(LT);
    case '>':
        return (peek() == '=') ? (nextChar(), Token(GTEQ)) : Token(GT);
    case '\"':
        nextChar();
        startPos = curPos;
        while (curChar != '\"')
        {
            nextChar();
        }
        text = source.substr(startPos, curPos - startPos);
        return Token(STRING, text);
    default:
        if (isalpha(curChar))
        {
            startPos = curPos;
            while (isalnum(peek()))
            {
                nextChar();
            }
            text = source.substr(startPos, curPos - startPos + 1);
            TokenType t = isKeyword(text);
            return (t != UNKNOWN) ? Token(t, text) : Token(ID, text);
        }
        else if (isdigit(curChar))
        {
            startPos = curPos;
            while (isdigit(peek()))
            {
                nextChar();
            }
            if (peek() == '.')
            {
                nextChar();
                if (!isdigit(peek()))
                {
                    abort("it must be number\n");
                }
                else
                {
                    nextChar();
                }
                while (isdigit(peek()))
                {
                    nextChar();
                }
            }
            text = source.substr(startPos, curPos - startPos + 1);
            return Token(NUMBER, text);
        }
        else if (isEOF(_EOF))
        {
            text = source.substr(curPos, 1);
            return Token(_EOF);
        }
        return Token(UNKNOWN);
    }
}

char Lexer::getCurChar() const
{
    return curChar;
}

bool Lexer::checkIsKeyword(const Token& token)
{
	for(const auto& keyword : keywords)
	{
        if (keyword.first == token.value)
        {
            return true;
        }
	}

    return false;
}
