#pragma once

#include <memory>
#include <array>

#include "details.hpp"

bool isValidFunction(std::string& aCommand) {
    auto allCommands = std::make_unique<std::array<std::string, 15>>();
    *allCommands = {
        "cat", "pwd", "rename", "cp", "cut" "echo", "perm", 
        "repem", "ls", "cd", "mkdir", "rmdir", "cls", "exit"
    };
    if (in(*allCommands, aCommand)) {
        return true;
    }
    return false;
}