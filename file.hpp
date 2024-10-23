#pragma once

#include <fstream>
#include <string>
#include <filesystem>

#include "customexcept.hpp"

class File {
    std::string filename;
public:
    File(const std::string filename) 
        : filename(filename) {
            if (!std::filesystem::exists(filename)) {
                throw FileNotFoundException(("File not found: " + filename).c_str());
            }
        }

    void write(const std::string& string, std::ios_base::openmode mode = std::ios::out) {
        std::ofstream file(filename, mode);
        if (!file.is_open()) {
            throw FileWriteException(("Error opening file: " + filename).c_str());
        }
        file << string;
        file.close();
    }

    std::string read() {
        std::ifstream file(filename);
        std::string result, line;
        if (!file.is_open()) {
            throw FileReadException(("Error opening file: " + filename).c_str());
        }
        while (std::getline(file, line)) {
            result += line + "\n";
        }
        return result;
    }
};