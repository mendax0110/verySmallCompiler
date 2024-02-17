#include "../src/includes/parser.h"
#include "../src/includes/lexer.h"
#include "../src/includes/emitter.h"
#include <iostream>
#include <filesystem>

using namespace parserInternals;
using namespace lexerInternals;
using namespace emitterInternals;
using namespace std;


/// @brief This is the constructor of the Parser class
/// @param source This is the source code to be parsed
Parser::Parser(const string& source) 
    : indent_count(0), _lexer(make_shared<Lexer>(source)), _emitter(make_shared<Emitter>())
{
    nextToken();
    nextToken();
}

/// @brief This is the destructor of the Parser class
Parser::~Parser()
{
    cout << "------------------------\n";
    cout << "Parser object destroyed.\n";
    cout << "------------------------\n";
}

/// @brief This is the function to check the current token
/// @param t This is the token to be checked
/// @return THis will return the result of the check
bool Parser::checkToken(TokenType t) const
{
    return (currentToken.type == t);
}

/// @brief This is the function to peek the next token
/// @param t This is the token to be peeked
/// @return This will return the result of the peek
bool Parser::checkPeek(TokenType t) const
{
    return (peekToken.type == t);
}

/// @brief This is the function to abort the parser
/// @param message This is the message to be printed
void Parser::abort(const string& message)
{
	cout << message << "\n";
	throw runtime_error(message);
}

/// @brief This is the function, that looks for a match in the token
/// @param t This it the token to be matched
/// @return This will return false if the token is not matched, otherwise true
bool Parser::match(TokenType t)
{
    if (!checkToken(t))
    {
        abort("Expected " + tokenInternals::convertString(t) + " but found " + currentToken.value);
        return false;
    }
    return true;
}

/// @brief This is the function to get the next token
void Parser::nextToken()
{
    currentToken = peekToken;
    peekToken = _lexer->getToken();
}

/// @brief This is the function to emit the indentation
void Parser::emitIndentation()
{
    for (int i = 0; i < indent_count; i++)
    {
        _emitter->emit("\t");
    }
}

/// @brief This is the function to parse the program
void Parser::program()
{
    cout << "program\n";
    while (!checkToken(_EOF))
    {
        statement();
        debug();
    }

    cout << "exit program\n";
    cout << "Current token after program: " << currentToken.value << "\n";
}

/// @brief This is the function to end the parser, write emitter to file
/// @param output This is the output file
void Parser::end(const string& output)
{
	ofstream file;
    file.open(filesystem::path(output));
    _emitter->write(output);
    file.close();
}

/// @brief This is the function to parse all the differnet statements
void Parser::statement()
{
    string errorMessage = "No handling for token: " + currentToken.value;
    cout << "statement\n";

    switch(currentToken.type)
	{
		case PRINT:
			isPrint();
			break;
		case IF:
			isIf();
			break;
		case WHILE:
			isWhile();
			break;
        case FOR:
            isFor();
            break;
		case LET:
			isLet();
			break;
		case INPUT:
			isInput();
			break;
		case PASS:
			isPass();
			break;
        case NEWLINE:
            newLine();
            break;
        case _EOF:
            endOfFile();
            break;
		default:
            throw runtime_error(errorMessage);
            break;
	}

    cout << "Exit statement\n";
}

/// @brief This is the function to parse the pass statement
void Parser::isPass()
{
    emitIndentation();
    cout << "PASS\n";
    _emitter->emit("pass\n");
    nextToken();
    newLine();
}

/// @brief This is the function to parse the input statement
void Parser::isInput()
{
    emitIndentation();
    cout << "INPUT\n";
    nextToken();
    match(ID);
    _emitter->emit(currentToken.value + " = int(input())\n");
    nextToken();
    newLine();
}

/// @brief This is the function to parse the let statement
void Parser::isLet()
{
    emitIndentation();
    cout << "LET\n";
    nextToken();
    match(ID);
    _emitter->emit(currentToken.value);
    nextToken();
    match(EQ);
    _emitter->emit(" = ");
    nextToken();
    expression();
    _emitter->emit("\n");
    nextToken();
    newLine();
}

/// @brief This is the function to parse the while statement
void Parser::isWhile()
{
    emitIndentation();
    nextToken();
    _emitter->emit("while ");
    indent_count++;
    comparison();
    _emitter->emit(":\n");
    nextToken();
    newLine();
    while (!checkToken(ENDWHILE))
    {
        statement();
    }
    match(ENDWHILE);
    indent_count--;
    nextToken();
    newLine();
    cout << "exit isWhile\n";
}


/// @brief This is the function to parse the for statement
void Parser::isFor()
{
    emitIndentation();
    cout << "FOR\n";
    _emitter -> emit("for ");
    indent_count++;
    nextToken();
    match(ID);
    _emitter->emit(currentToken.value);
    nextToken();
    match(EQ);
    nextToken();
    nextToken();
    comparison();
    match(TO);
    _emitter->emit(" in ");
    nextToken();
    _emitter->emit("range(" + currentToken.value + ")");
    _emitter->emit(":\n");
    nextToken();
    newLine();
    while(!checkToken(ENDFOR))
	{
		statement();
	}
    match(ENDFOR);
    indent_count--;
    nextToken();
    newLine();
    cout << "exit FOR\n";
}


/// @brief This is the function to parse the if statement
void Parser::isIf()
{
    emitIndentation();
    cout << "IF\n";
    _emitter->emit("if ");
    indent_count++;
    nextToken();
    comparison();
    _emitter->emit(":\n");
    nextToken();
    newLine();
    while (!checkToken(ELSE) && !checkToken(ENDIF))
    {
        statement();
    }
    if (checkToken(ELSE))
    {
        cout << "ELSE\n";
        _emitter->emit("else:\n");
        nextToken();
        newLine();
        while (!checkToken(ENDIF))
        {
            statement();
        }
    }
    match(ENDIF);
    indent_count--;
    match(ENDIF);
    nextToken();
    newLine();
    cout << "exit IF\n";
}

/// @brief This is the function to parse the print statement
void Parser::isPrint()
{
    cout << "PRINT\n";
    nextToken();
    if (checkToken(STRING) || checkToken(NUMBER) || checkToken(ID))
    {
        emitIndentation();
        if (currentToken.type == STRING)
        {
            _emitter->emit("print(\"" + currentToken.value + "\")\n");
        }
        else if (currentToken.type == NUMBER || currentToken.type == ID)
        {
            _emitter->emit("print(" + currentToken.value + ")\n");
        }
    }
    else
    {
        statement();
    }
    nextToken();
    newLine();
    cout << "exit PRINT\n";
}

/// @brief This is the function to check if the token is a comparison operator
/// @return This is the result of the check
bool Parser::isCompareOps() const
{
    return (peekToken.type > START_COMPARE_OPS && peekToken.type < END_COMPARE_OPS);
}

/// @brief This is the function to parse the comparison
void Parser::comparison()
{
    cout << "comparison\n";
    expression();
    if (isCompareOps())
    {
        nextToken();
        _emitter->emit(" " + currentToken.value + " ");
        nextToken();
        expression();
    }
    while (isCompareOps())
    {
        nextToken();
        _emitter->emit(" " + currentToken.value + " ");
        nextToken();
        expression();
        _emitter->emit(currentToken.value);
    }
    cout << "exit comparison\n";
}

/// @brief This is the function to parse the expression
void Parser::expression()
{
    cout << "expression\n";
    term();
    while (checkPeek(MINUS) || checkPeek(PLUS))
    {
        nextToken();
        _emitter->emit(" " + currentToken.value + " ");
        nextToken();
        term();
    }
    cout << "exit expression\n";
}

/// @brief This is the function to parse the term
void Parser::term()
{
    cout << "term\n";
    unary();
    while (checkPeek(ASTERISK) || checkPeek(SLASH))
    {
        nextToken();
        _emitter->emit(" " + currentToken.value + " ");
        nextToken();
        unary();
    }
    cout << "exit term\n";
}

/// @brief This is the function to parse the unary
void Parser::unary()
{
    cout << "unary\n";
    if (checkToken(PLUS) || checkToken(MINUS))
    {
        _emitter->emit(currentToken.value);
        nextToken();
    }
    primary();
}

/// @brief This is the function to parse the primary
void Parser::primary()
{
    cout << "primary ";
    if (checkToken(NUMBER) || checkToken(ID))
    {
        cout << currentToken.value << "\n";
        _emitter->emit(currentToken.value);
    }
    cout << "exit primary\n";
}

/// @brief This is the function to parse the new line
void Parser::newLine()
{
    cout << "newLine\n";
    cout << "Current token before matching NEWLINE: " << currentToken.value << " (" << currentToken.type << ")\n";

    if (checkToken(NEWLINE))
    {
        match(NEWLINE);
        while (checkToken(NEWLINE))
        {
            _emitter->emit("\n");
            nextToken();
        }
    }
}

/// @brief This is the function to parse the end of file
void Parser::endOfFile()
{
    cout << "endOfFile\n";
    match(_EOF);
    _emitter->emit("\n");
    cout << "exit endOfFile\n";
}

/// @brief This is the function to debug the currentToken/peekToken value and type
void Parser::debug() const
{
    cout << "Current token: " << currentToken.value << " (" << currentToken.type << ")\n";
	cout << "Peek token: " << peekToken.value << " (" << peekToken.type << ")\n";
}
