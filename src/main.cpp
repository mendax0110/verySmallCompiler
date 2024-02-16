#include "../src/includes/tokenizer.h" 
#include "../src/includes/lexer.h"
#include "../src/includes/parser.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <memory>

using namespace lexerInternals;
using namespace tokenInternals;
using namespace parserInternals;
using namespace std;
namespace fs = filesystem;


const string outputDirectory = "../outputLang/";

/// @brief This is the function to process the file for the compiler
/// @param inputFilePath These are the input files
void processFile(const fs::path& inputFilePath) 
{
    ifstream inFile(inputFilePath);

    if (!inFile.is_open()) 
    {
        cerr << "Error: Unable to open input file: " << inputFilePath << endl;
        return;
    }

    cout << "Processing input file: " << inputFilePath << endl;

    stringstream strStream;
    strStream << inFile.rdbuf();
    string source = strStream.str();

    Lexer lexer(source);
    Token token = lexer.getToken();
    while (!lexer.isEOF(token)) {
        cout << token.value << "\n" << endl;
        token = lexer.getToken();
    }

    Parser parser(source);
    parser.program();
    cout << "Parsing completed\n";

    string outputFileName = outputDirectory + inputFilePath.stem().string() + ".py";
    fs::path outputFilePath = outputFileName;

    parser.end(outputFilePath.string());
}

/// @brief This is the main function for the compiler
/// @return This will return 0 if the program runs successfully
int main() 
{
    const string inputDirectory = "../inputLang/";

    for (const auto& entry : fs::directory_iterator(inputDirectory))
    {
        if (entry.is_regular_file())
        {
            processFile(entry.path());
        }
    }

    return 0;
}
