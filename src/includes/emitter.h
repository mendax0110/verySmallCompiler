#ifndef EMITTER_H
#define EMITTER_H

#include <iostream>
#include <string>
#include <fstream>

namespace emitterInternals 
{
    class Emitter
    {
    public:
        Emitter();
        ~Emitter();

        void emit(std::string c);
        void emitLine(std::string c);
        void write(std::string output);
        
    private:
        std::string code;
    };

}

#endif // EMITTER_H