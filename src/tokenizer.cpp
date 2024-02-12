#include "../src/includes/tokenizer.h"

using namespace tokenInternals;
using namespace std;

Token::Token()
{
    type = UNKNOWN;
    value = convertString(type);
}

Token::~Token()
{
    cout << "-----------------------\n";
    cout << "Token object destroyed.\n";
    cout << "-----------------------\n";
}

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
    }
    return text;
}

TokenType tokenInternals::isKeyword(const string &text)
{
    unordered_map<string,TokenType>::const_iterator got = keywords.find(text);
    if (got == keywords.end())
        return UNKNOWN;
    else
        return got->second;
}

void Token::operator=(const Token& rhs)
{
    this->type = rhs.type;
    this->value = std::move(rhs.value);
}