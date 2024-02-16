#include "../src/includes/emitter.h"
#include <iostream>
#include <fstream>

using namespace emitterInternals;
using namespace std;


/// @brief This is the constructor for the Emitter class
Emitter::Emitter()
{
    code = "";
}

/// @brief This is the destructor for the Emitter class
Emitter::~Emitter()
{
    cout << "-------------------------\n";
    cout << "Emitter object destroyed.\n";
    cout << "-------------------------\n";
}

/// @brief This is the emit function that emit a line of code
/// @param c This is the line of code to be emitted
void Emitter::emit(string c)
{
    code += c;
}

/// @brief This is the emitLine function that emits a line of code and adds a newline character
/// @param c This is the line of code to be emitted
void Emitter::emitLine(string c)
{
    code += c + "\n";
}

/// @brief This is the write function that writes the output to a file
/// @param output This is the output file
void Emitter::write(string output)
{
    ofstream out(output);
    out << code;
    out.close();
    cout << "--------------------------------\n";
    cout << "OutputFile written successfully.\n";
    cout << "--------------------------------\n";
}
