#include "../src/includes/tokenizer.h"

using namespace tokenInternals;
using namespace std;


/// @brief This is the constructor for the Token class
Token::Token()
{
    type = UNKNOWN;
    value = convertString(type);
}

/// @brief This is the destructor for the Token class
Token::~Token()
{
    cout << "-----------------------\n";
    cout << "Token object destroyed.\n";
    cout << "-----------------------\n";
}

/// @brief This is the function for the tokens
/// @param t This is the parameter for the Token Type
/// @param v This is the parameter for the string value
Token::Token(TokenType t, string v)
{
    type = t;
    if (v.length() == 0)
    {
        value = convertString(t);
    }
    else
    {
        value = std::move(v);
    }
}

/// @brief This is the function to convert the string
/// @param t This it the Token Type we have to convert
/// @return This will return the converted token
string tokenInternals::convertString(TokenType t)
{
    string text;
    switch(t)
    {
    case UNKNOWN:
        text = "UNKNOWN";
        break;
    case _EOF:
        text = "EOF";
        break;
    case NEWLINE:
        text = "NEWLINE";
        break;
    case NUMBER:
        text = "NUMBER";
        break;
    case ID:
        text = "ID";
        break;
    case STRING:
        text = "STRING";
        break;
    case PRINT:
        text = "PRINT";
        break;
    case INPUT:
        text = "INPUT";
        break;
    case LET:
        text = "LET";
        break;
    case IF:
        text = "IF";
        break;
    case PASS:
        text = "PASS";
        break;
    case ELSE:
        text = "ELSE";
        break;    
    case THEN:
        text = "THEN";
        break;
    case ENDIF:
        text = "ENDIF";
        break;
    case WHILE:
        text = "WHILE";
        break;
    case ENDWHILE:
        text = "ENDWHILE";
        break;
    case EQ:
        text = "=";
        break;
    case PLUS:
        text = "+";
        break;
    case MINUS:
        text = "-";
        break;
    case ASTERISK:
        text = "*";
        break;
    case SLASH:
        text = "\"";
        break;
    case EQEQ:
        text = "==";
        break;
    case NOTEQ:
        text = "!=";
        break;
    case LT:
        text = "<";
        break;
    case LTEQ:
        text = "<=";
        break;
    case GT:
        text = ">";
        break;
    case GTEQ:
        text = ">=";
        break;
    default:
        text = "";
        break;
    }
    return text;
}

/// @brief This is the function to check if the token is a keyword
/// @param text This is the text to be checked
/// @return This will return the token type
TokenType tokenInternals::isKeyword(const string &text)
{
    unordered_map<string,TokenType>::const_iterator got = keywords.find(text);
    if (got == keywords.end())
        return UNKNOWN;
    else
        return got->second;
}

/// @brief This is the function for the operator Token
/// @param rhs This is the token to be assigned
void Token::operator=(const Token& rhs)
{
    this->type = rhs.type;
    this->value = std::move(rhs.value);
}