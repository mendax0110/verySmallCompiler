#include "../src/includes/lexer.h"
#include "../src/includes/tokenizer.h"
#include <cctype>

using namespace lexerInternals;
using namespace tokenInternals;
using namespace std;


/// @brief This is the constructor for the Lexer class
/// @param This is the source code to be lexed
Lexer::Lexer(string src)
    : source(src + "\n"), curChar(0), curPos(-1), sourceLen(static_cast<int>(source.length()))
{
}

/// @brief This is the destructor for the Lexer class
Lexer::~Lexer()
{
    cout << "-----------------------\n";
    cout << "Lexer Object destroyed.\n";
    cout << "-----------------------\n";
}

/// @brief This is the function that gets the next character
void Lexer::nextChar()
{
    curPos += 1;
    curChar = (curPos >= sourceLen) ? '\0' : source[curPos];
}

/// @brief This is the function that peeks the next character
/// @return This will return the peek to the next character
char Lexer::peek() const
{
    if (curPos == std::numeric_limits<decltype(curPos)>::max())
        return '\0';
    else
        return (curPos + 1 >= sourceLen) ? '\0' : source[curPos + 1];
}

/// @brief This is the function that checks if the token is the end of file
/// @param token This is the token to be checked
/// @return This will return the result of the check
bool Lexer::isEOF(const Token &token) const
{
    return (token.type == _EOF);
}

/// @brief This is the funciton that skips the whitespace
void Lexer::skipWhitespace()
{
    while (isspace(curChar))
    {
        nextChar();
    }
}

/// @brief This is the function that skips the comment
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

/// @brief This is the function that aborts the lexer
/// @param message This is the reason message for the abort
void Lexer::abort(string message)
{
    cout << "Error: " + message + "\n";
    assert(0==1);
}

/// @brief This is the function that gets the token
/// @return This will return the token
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

/// @brief This is the function to get the current char
/// @return This will return the current char
char Lexer::getCurChar() const
{
    return curChar;
}

/// @brief This is the function to check if the token is a keyword
/// @param token This is the token to be checked
/// @return This will return true it the keyword and token match
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

void Lexer::lexRecursively()
{
    Token token = getToken();
    
    while (!isEOF(token))
    {
        if (token.type == NEWLINE)
        {
			token = getToken();
            //lexRecursively();
		}
        else if (token.type == _EOF)
        {
			break;
		}
        else if (token.type == UNKNOWN)
        {
			abort("Unknown token");
		}
        else
        {
            if (checkIsKeyword(token))
            {
				cout << "Keyword: " << token.value << endl;
			}
            else
            {
				cout << "Token: " << token.value << endl;
			}
			token = getToken();
		}
	}
}
