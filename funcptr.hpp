#pragma once

#include <map>
#include <string>
#include <functional>
#include <cstdlib>

#include "file.hpp"

// Define a type for the command functions
using FileFunc = std::function<std::string()>;
using Box = std::unique_ptr<File>;

FileFunc getFunctionOfExistFile(std::string name_of_function, 
                                        Box& file, 
                                        const std::vector<std::string>& arguments) 
{
const std::map<std::string, FileFunc> FILE_EXIST_COMMAND_MAP = {
        {"cat", [&file, arguments]() {
            return file->readFile();
        }},
        {"echo", [&file, arguments]() {
            file->writeFile(arguments.at(2));
            return std::string{""};
        }},
        {"rename", [&file, arguments]() {
            file->renameFile(arguments.at(2));
            return std::string{""};
        }},
        {"copy", [&file, arguments]() {
            file->copyFile(arguments.at(2));
            return std::string{""};
        }},
        {"cut", [&file, arguments]() {
            // arguments.at(2) is path without file
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

FileFunc getFunctionOfMDFile(const std::string& name_of_function, 
                                    const std::vector<std::string>& tokens)
{
    const std::map<std::string, FileFunc> functions = {
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

using DirFunc = std::function<std::vector<std::string>()>;

DirFunc getFunctionOfDirectory(const std::string& name_of_function, 
                                const std::string parameter = getCurrentWorkingDirectory()) 
{
    const std::map<std::string, DirFunc> functions = {
        {"ls", [parameter]() {
            return getFilesAndDirectories(parameter);
        }},
        {"mkdir", [parameter]() {
            createDirectory(parameter);
            return std::vector<std::string>();
        }},
        {"rmdir", [parameter]() {
            deleteDirectory(parameter);
            return std::vector<std::string>();
        }},
        {"cd", [parameter]() {
            changeDirectory(parameter);
            return getFilesAndDirectories(parameter);
        }},
        {"cls", []() {
            #ifdef _WIN32
                std::system("cls");
            #else
                std::system("clear");
            #endif
            return std::vector<std::string>();
        }}
    };
    return functions.at(name_of_function);
}