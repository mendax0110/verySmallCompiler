#ifndef EMITTER_H
#define EMITTER_H

#include <iostream>
#include <string>
#include <fstream>

/// @brief Namespace for the emitter internals \namespace emitterInternals
namespace emitterInternals 
{
    /// @brief Class for the emitter \class Emitter
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