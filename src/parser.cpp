#include "../src/includes/parser.h"
#include "../src/includes/lexer.h"
#include "../src/includes/emitter.h"
#include <iostream>

using namespace parserInternals;
using namespace lexerInternals;
using namespace emitterInternals;
using namespace std;

const string inputFile = "input.tt";
const string outputFile = "output.py";
const string inputFilePath = "../inputLang/" + inputFile;
const string outputFilePath = "../outputLang/" + outputFile;

Parser::Parser(const string& source) : indent_count(0), _lexer(make_shared<Lexer>(source)), _emitter(make_shared<Emitter>())
{
    nextToken();
    nextToken();
}

bool Parser::checkToken(TokenType t)
{
    return (currentToken.type == t);
}

bool Parser::checkPeek(TokenType t)
{
    return (peekToken.type == t);
}

void Parser::abort(const std::string& message)
{
	cout << message << "\n";
	exit(1);
}

bool Parser::match(TokenType t)
{
    if (!checkToken(t))
    {
        cout << "expect " << t << " != " << currentToken.type << "\n";
        Parser::abort("Token doesn't match but it must match token");
    }
    return true;
}

void Parser::nextToken()
{
    currentToken = peekToken;
    peekToken = _lexer->getToken();
}

void Parser::emitIndentation()
{
    for (int i = 0; i < indent_count; i++)
    {
        _emitter->emit("\t");
    }
}

void Parser::program()
{
    cout << "program\n";
    while (!checkToken(_EOF))
    {
        statement();
    }
}

void Parser::end(const std::string& output)
{
	ofstream file;
	file.open(outputFilePath);
	file << output;
	file.close();
}

void Parser::statement()
{
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
		case LET:
			isLet();
			break;
		case INPUT:
			isInput();
			break;
		case PASS:
			isPass();
			break;
		default:
            runtime_error("no match in switch statement");
			break;
	}
}

void Parser::isPass()
{
    emitIndentation();
    cout << "PASS\n";
    _emitter->emit("pass\n");
    nextToken();
    newLine();
}

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
}

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
        emitIndentation();
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
    nextToken();
    newLine();
    cout << "exit IF\n";
}

void Parser::isPrint()
{
    cout << "PRINT\n";
    nextToken();
    if (checkToken(STRING) || checkToken(NUMBER) || checkToken(ID))
    {
        emitIndentation();
        if (currentToken.type == STRING)
        {
            _emitter->emit("print (\"" + currentToken.value + "\")\n");
        }
        else if (currentToken.type == NUMBER || currentToken.type == ID)
        {
            _emitter->emit("print (" + currentToken.value + ")\n");
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

bool Parser::isCompareOps()
{
    return (peekToken.type > START_COMPARE_OPS && peekToken.type < END_COMPARE_OPS);
}

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
}

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
}

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
}

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

void Parser::primary()
{
    cout << "primary ";
    if (checkToken(NUMBER) || checkToken(ID))
    {
        cout << currentToken.value << "\n";
        _emitter->emit(currentToken.value);
    }
}

void Parser::newLine()
{
    match(NEWLINE);
    while (checkToken(NEWLINE))
    {
        nextToken();
    }
}