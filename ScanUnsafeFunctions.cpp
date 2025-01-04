#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>

void scanFile(const std::string& filename, const std::vector<std::string>& unsafeFunctions) 
{
    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 0;
    std::regex unsafeRegex(R"(\b(" + std::string(unsafeFunctions[0]) + R"(\b|)" + std::string(unsafeFunctions[1]) + R"(\b|)" + std::string(unsafeFunctions[2]) + R"(\b|)" + std::string(unsafeFunctions[3]) + R"(\b))");

    while (std::getline(file, line)) 
    {
        lineNumber++;
        if (std::regex_search(line, unsafeRegex)) 
        {
            std::cout << "Potential vulnerability found in " << filename << " at line " << lineNumber << ": " << line << std::endl;
        }
    }

    file.close();
}

int main() 
{
    std::vector<std::string> unsafeFunctions = {"strcpy", "strcat", "sprintf", "gets"};
    std::string filename;

    std::cout << "Enter the C++ source file to scan: ";
    std::cin >> filename;

    scanFile(filename, unsafeFunctions);

    return 0;
}
