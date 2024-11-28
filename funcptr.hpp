#pragma once

#include <map>
#include <string>
#include <functional>

#include "file.hpp"

// Define a type for the command functions
using CommandFunction = std::function<std::string()>;
using Box = std::unique_ptr<File>;

CommandFunction getFunctionOfExistFile(std::string name_of_function, 
                                        Box& file, 
                                        const std::vector<std::string>& arguments) 
{
const std::map<std::string, CommandFunction> FILE_EXIST_COMMAND_MAP = {
        {"cat", [&file, arguments]() {
            return file->readFile();
        }},
        {"echo", [&file, arguments]() {
            file->writeFile(arguments[2]);
            return std::string{""};
        }},
        {"rename", [&file, arguments]() {
            file->renameFile(arguments[2]);
            return std::string{""};
        }},
        {"copy", [&file, arguments]() {
            file->copyFile(arguments[2]);
            return std::string{""};
        }},
        {"cut", [&file, arguments]() {
            file->copyFile(arguments.at(2));
            deleteFile(arguments.at(1));
            return std::string{""};
        }},
        {"pwd", [&file, arguments]() {
            return file->pwdFile();
        }}
    };
    return FILE_EXIST_COMMAND_MAP.at(name_of_function);
}

CommandFunction getFunctionOfMDFile(const std::string& name_of_function, 
                                    const std::vector<std::string>& tokens) {
    const std::map<std::string, CommandFunction> functions = {
        {"touch", [tokens](){
            createFile(tokens.at(1));
            return std::string{"File created"};
        }},
        {"rm", [tokens](){
            deleteFile(tokens.at(1));
            return std::string{"File deleted"};
        }}
    };
    return functions.at(name_of_function);
}


