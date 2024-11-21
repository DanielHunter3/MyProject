#pragma once

#include <cstdint>
#include <array>
#include <iostream>

#include "usercommand.hpp"

std::vector<std::string> getCommand(std::string command) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(command);
    while (std::getline(tokenStream, token, ' ')) {
        tokens.push_back(token);
    }
    return tokens;
}

void terminal(std::vector<std::string>& tokens) {
    if (tokens.size() == 0) {
        throw std::runtime_error("The command line is empty");
    }
    std::string command = tokens[0];
    int8_t quantityOfParameters = tokens.size() - 1;

    const std::array<std::string, 3> directoryCommands { "cd", "mkdir", "rmdir" };
    const std::array<std::string, 9> fileCommands { "make", "remove", "cat", 
                                                    "echo", "rename", "copy", 
                                                    "perm", "repem", "cut" };

    if (in(directoryCommands, command)) {
        for (const auto& i: directoryUserCommand(tokens, command, quantityOfParameters)){
            std::cout << i << std::endl;
        }
    }
    else if (in(fileCommands, command)) {
        std::cout << fileUserCommand(tokens, command, quantityOfParameters);
    }
}

