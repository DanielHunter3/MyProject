#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "customexcept.hpp"
#include "filemenager.hpp"
#include "file.hpp"
#include "directory.hpp"
#include "details.hpp"
#include "funcptr.hpp"

std::vector<std::string> directoryUserCommand(const std::vector<std::string>& tokens,
                        const std::string& aCommand, 
                        int8_t& quantityOfParameters) 
{
    if (aCommand != "ls") {
        //----------------------------------------------------------------
        if (quantityOfParameters == 0) {
            throw std::invalid_argument("Missing directory name");
        }
        //----------------------------------------------------------------
        if (aCommand == "mkdir") { createDirectory(tokens[1]); }
        else if (aCommand == "rmdir") { deleteDirectory(tokens[1]); }
        else if (aCommand == "cd") {
            changeDirectory(tokens[1]);
            return getFilesAndDirectories(getCurrentWorkingDirectory());
        }
    }
    else {
        //----------------------------------------------------------------
        if (quantityOfParameters != 0) {
            throw std::invalid_argument("Too many arguments for 'ls' command");
        }
        //----------------------------------------------------------------
        return getFilesAndDirectories(getCurrentWorkingDirectory());
    }

    return std::vector<std::string>();
}

// Почему не работает touch?
std::string fileUserCommand(const std::vector<std::string>& tokens,
                        const std::string& aCommand, 
                        int8_t& quantityOfParameters) 
{
    const std::array<std::string, 2> minOneParameters { "cat", "pwd" };
    const std::array<std::string, 4> minTwoParameters { "rename", "cp", "cut" "echo" };
    const std::array<std::string, 2> minThreeParameters { "perm", "repem" };

    if (aCommand == "touch" || aCommand == "rm") {
        return getFunctionOfMDFile(aCommand, tokens)();
    }

    try {
        std::unique_ptr<File> file(new File(tokens.at(1)));

        if (in(minOneParameters, aCommand)) {
            //----------------------------------------------------------------
            if (quantityOfParameters < 1) {
                throw std::invalid_argument("Invalid number of parameters (qop < 1)\n");
            }
            //----------------------------------------------------------------
            return getFunctionOfExistFile(aCommand, file, tokens)();
        }
        else if (in(minTwoParameters, aCommand)) {
            //----------------------------------------------------------------
            if (quantityOfParameters < 2) {
                throw std::invalid_argument("Invalid number of parameters (qop < 2)\n");
            }
            //----------------------------------------------------------------
            return getFunctionOfExistFile(aCommand, file, tokens)();
        }
        else if (in(minThreeParameters, aCommand)) {
            //----------------------------------------------------------------
            if (quantityOfParameters < 3) {
                throw std::invalid_argument("Invalid number of parameters (qop < 3)\n");
            }
            //----------------------------------------------------------------
            //...
            return getFunctionOfExistFile(aCommand, file, tokens)();
        }
        else {
            throw std::invalid_argument("Invalid command");
        }
    }
    catch (const std::out_of_range &e) { 
        return std::string("Invalid argument: <command> \'argument: is not found\'\n");
    }
    catch (std::exception &e) { return e.what(); }

    return std::string{""};
}
