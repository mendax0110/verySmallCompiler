#include "../src/includes/emitter.h"
#include <iostream>
#include <fstream>

using namespace emitterInternals;
using namespace std;

Emitter::Emitter()
{
    code = "";
}

void Emitter::emit(std::string c)
{
    code += c;
}

void Emitter::emitLine(std::string c)
{
    code += c + "\n";
}

void Emitter::write(std::string output)
{
    ofstream out(output);
    out << code;
    out.close();
    cout << "OutputFile written successfully.\n";
}
