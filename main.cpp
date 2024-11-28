#include <filesystem>
#include <iostream>
#include <string>

#include "terminal.hpp"

int main() {
    std::string s;
    while (true)
    {
        try {
            getTerminal(setTerminal());
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << '\n';
        }
    }
}