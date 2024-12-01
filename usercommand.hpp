#pragma once

#include <iostream>
#include <memory>

#include "filemenager.hpp"
#include "file.hpp"
#include "directory.hpp"
#include "details.hpp"
#include "funcptr.hpp"

std::vector<std::string> directoryUserCommand(const std::vector<std::string>& tokens,
                        const std::string& aCommand, 
                        int8_t& quantityOfParameters) 
{
    if (aCommand != "ls" && aCommand != "cls") {
        //----------------------------------------------------------------
        if (quantityOfParameters == 0) {
            throw std::invalid_argument("Missing directory name");
        }
        //----------------------------------------------------------------
        getFunctionOfDirectory(aCommand, tokens.at(1))();
    }
    else {
        //----------------------------------------------------------------
        if (quantityOfParameters != 0) {
            throw std::invalid_argument("Too many arguments for command");
        }
        //----------------------------------------------------------------
        getFunctionOfDirectory(aCommand)();
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

    try {
        if (aCommand == "touch" || aCommand == "rm") {
            return getFunctionOfMDFile(aCommand, tokens)();
        }

        std::unique_ptr<File> file(new File(tokens.at(1)));

        if (in(minOneParameters, aCommand) && quantityOfParameters < 1) {
            throw std::invalid_argument("Invalid number of parameters (qop < 1)\n");
        }
        else if (in(minTwoParameters, aCommand) && quantityOfParameters < 2) {
            throw std::invalid_argument("Invalid number of parameters (qop < 2)\n");
        }
        else if (in(minThreeParameters, aCommand) && quantityOfParameters < 3) {
            throw std::invalid_argument("Invalid number of parameters (qop < 3)\n");
        }

        return getFunctionOfExistFile(aCommand, file, tokens)();
    }
    catch (const std::out_of_range &e) { 
        return std::string("Invalid argument: <command> \'argument: is not found\'\n");
    }
    catch (std::exception &e) { return e.what(); }

    return std::string{""};
}
