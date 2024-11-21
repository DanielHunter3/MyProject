#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include "customexcept.hpp"
#include "filemenager.hpp"
#include "file.hpp"
#include "directory.hpp"
#include "details.hpp"

std::vector<std::string> directoryUserCommand(const std::vector<std::string>& tokens,
                        const std::string& command, 
                        int8_t& quantityOfParameters) 
{
    if (command != "ls") {
        //----------------------------------------------------------------
        if (quantityOfParameters == 0) {
            throw std::invalid_argument("Missing directory name");
        }
        //----------------------------------------------------------------
        if (command == "mkdir") { createDirectory(tokens[1]); }
        else if (command == "rmdir") { deleteDirectory(tokens[1]); }
        else if (command == "cd") {
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

std::string fileUserCommand(const std::vector<std::string>& tokens,
                        const std::string& command, 
                        int8_t& quantityOfParameters) 
{
    const std::array<std::string, 2> minOneParameters { "cat", "rm" };
    const std::array<std::string, 5> minTwoParameters { "touch", "rename", "copy", "cut", "pwd" };
    const std::array<std::string, 2> minThreeParameters { "perm", "repem" };

    try {
        std::unique_ptr<File> file(new File(tokens.at(1)));

        if (in(minOneParameters, command)) {
            //----------------------------------------------------------------
            if (quantityOfParameters < 1) {
                throw std::invalid_argument("invalid number of parameters");
            }
            //----------------------------------------------------------------
            if (command == "cat")  { return file->readFile(); }
            else if (command == "rm") { deleteFile(tokens[1]); }
        }
        else if (in(minTwoParameters, command)) {
            //----------------------------------------------------------------
            if (quantityOfParameters < 2) {
                throw std::invalid_argument("invalid number of parameters");
            }
            //----------------------------------------------------------------
            if (command == "touch") { file->writeFile(tokens[2]); }
            else if (command == "rename") { file->renameFile(tokens[2]); }
            else if (command == "copy") { file->copyFile(tokens[2]); }
            else if (command == "cut") { 
                file->copyFile(tokens[2]);
                deleteFile(tokens[1]);
            }
            else if (command == "pwd")  { return file->pwdFile(); }
        }
        else if (in(minThreeParameters, command)) {
            //...
        }
    }
    catch (const FileNotFoundException &e) {
        if (command == "touch") { createFile(tokens[1]); }
        else { return e.what(); }
    }
    catch (const std::out_of_range &e) { 
        return std::string("Invalid argument: <command> \'argument: is not found\'");
    }
    catch (std::exception &e) { return e.what(); }

    return std::string{"\0"};
}