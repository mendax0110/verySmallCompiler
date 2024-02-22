#include <iostream>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <string>
#include <filesystem>


/// @brief Namespace for the linter internals \namespace linterInternals
namespace linterInternals
{
    /// @brief Class for the linter for generated python files \class Linter
    class Linter
    {
    public:
        Linter();
        ~Linter();

        void lint();

    private:
        std::string code;
        std::unordered_map<std::string, std::string> keywords;
        const std::filesystem::path outputDirectory = "../outputLang/";

        const std::list<std::string> keywordsList = {
            "False", "None", "True", "and", "as", "assert",
            "async", "await", "break", "class", "continue",
            "def", "del", "elif", "else", "except", "finally",
            "for", "from", "global", "if", "import", "in", "is",
            "lambda", "nonlocal", "not", "or", "pass", "raise",
            "return", "try", "while", "with", "yield"
        };
    };
}