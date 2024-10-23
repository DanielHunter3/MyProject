#pragma once

#include <filesystem>
#include <vector>
#include <string>

std::vector<std::string> getCommand(std::string command) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(command);
    while (std::getline(tokenStream, token, ' ')) {
        tokens.push_back(token);
    }
    return tokens;
}
