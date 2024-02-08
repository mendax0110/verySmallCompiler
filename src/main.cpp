#include "../src/includes/tokenizer.h" 
#include "../src/includes/lexer.h"
#include "../src/includes/parser.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

using namespace lexerInternals;
using namespace tokenInternals;
using namespace parserInternals;
using namespace std;

const string inputFile = "input.tt";
const string outputFile = "output.py";
const string inputFilePath = "../inputLang/" + inputFile;
const string outputFilePath = "../outputLang/" + outputFile;

int main() 
{
    ifstream inFile;

    if (inFile.is_open())
    {
        cerr << "Error: Unable to open input file." << endl;
        return 1;
    }
    else
    {
        cout << "Input file opened successfully." << endl;
        inFile.open(inputFilePath);
    }

    stringstream strStream;
    strStream << inFile.rdbuf();
    string source = strStream.str();
    
	Lexer lexer(source);
    Token token = lexer.getToken();
	while (!lexer.isEOF(token))
    {
		cout << token.value << "\n" << endl;
        token = lexer.getToken();
    }
    
    Parser parser (source);
    parser.program();
    cout << "Parsing completed\n";
    parser.end(inputFilePath);

    Emitter emit;
    emit.write(outputFilePath);
    
    return 0;
}