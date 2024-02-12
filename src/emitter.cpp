#include "../src/includes/emitter.h"
#include <iostream>
#include <fstream>

using namespace emitterInternals;
using namespace std;

Emitter::Emitter()
{
    code = "";
}

Emitter::~Emitter()
{
    cout << "-------------------------\n";
    cout << "Emitter object destroyed.\n";
    cout << "-------------------------\n";
}

void Emitter::emit(string c)
{
    code += c;
}

void Emitter::emitLine(string c)
{
    code += c + "\n";
}

void Emitter::write(string output)
{
    ofstream out(output);
    out << code;
    out.close();
    cout << "--------------------------------\n";
    cout << "OutputFile written successfully.\n";
    cout << "--------------------------------\n";
}
