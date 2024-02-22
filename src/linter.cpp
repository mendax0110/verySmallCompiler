#include "../src/includes/linter.h"

using namespace linterInternals;
using namespace std;
namespace fs = std::filesystem;

/// @brief This is the constructor for the Linter class
Linter::Linter()
{
    code = "";
}

/// @brief This is the destructor for the Linter class
Linter::~Linter()
{
    cout << "-----------------------\n";
    cout << "Linter object destroyed.\n";
    cout << "-----------------------\n";
}

/// @brief This is the lint function that lints the output files
void Linter::lint()
{
    if (!fs::exists(outputDirectory))
    {
        throw runtime_error("Output directory does not exist");
    }

    for (const auto& entry : fs::directory_iterator(outputDirectory))
    {
        if (entry.is_regular_file())
        {
            const fs::path filePath = entry.path();
            ifstream file(filePath);

            if (file.is_open())
            {
                string line;
                while (getline(file, line))
                {
                    std::cout << line << std::endl;
                }
                file.close();
            }
            else
            {
                throw runtime_error("Error opening file: " + filePath.string());
            }

            string autopep8Command = "autopep8 --in-place --aggressive --aggressive " + filePath.string();
            string pylintCommand = "pylint " + filePath.string();

            system(autopep8Command.c_str());
            system(pylintCommand.c_str());
        }
    }
}