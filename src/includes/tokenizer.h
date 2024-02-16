#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <iostream>
#include <string>
#include <unordered_map>

/// @brief Namespace for the token internals \namespace tokenInternals
namespace tokenInternals 
{
    typedef enum
    {
        UNKNOWN,
        START_GENERALS,
        _EOF,
        NEWLINE,
        NUMBER,
        ID,
        STRING,
        END_GENERALS,
        START_KEYWORDS,
        PRINT,
        INPUT,
        LET,
        IF,
        PASS,
        ELSE,
        THEN,
        ENDIF,
        WHILE,
        ENDWHILE,
        END_KEYWORDS,
        START_OPERATORS,
        EQ,
        PLUS,
        MINUS,
        ASTERISK,
        SLASH,
        END_OPERATORS,
        START_COMPARE_OPS,
        EQEQ,
        NOTEQ,
        LT,
        LTEQ,
        GT,
        GTEQ,
        END_COMPARE_OPS,
        NUM_TOKENTYPES
    } TokenType;

    const std::unordered_map<std::string, TokenType> keywords = {{"PRINT", PRINT},
                                                                {"INPUT",INPUT},
                                                                {"LET", LET},
                                                                {"IF", IF},
                                                                {"PASS", PASS},
                                                                {"ELSE", ELSE},
                                                                {"THEN", THEN},
                                                                {"ENDIF", ENDIF},
                                                                {"WHILE", WHILE},
                                                                {"ENDWHILE", ENDWHILE},
                                                                {"EOF", _EOF},
                                                                {"NEWLINE", NEWLINE}};
    std::string convertString(TokenType t);
    TokenType isKeyword(const std::string &text);

    /// @brief Class for the token \class Token
    class Token
    {
    public:
        Token();
        ~Token();
        Token(TokenType t, std::string v="");
        void operator=(const Token& rhs);
        std::string value;
        TokenType type;
    };
}

#endif // TOKENIZER_H