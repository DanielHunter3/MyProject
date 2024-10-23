#pragma once

#include <sys/stat.h>
#include <string>

#include "customexcept.hpp"

void create_directory(const std::string& dirname) {
    if (mkdir(dirname.c_str()) == -1) {
        throw CreateDirectoryException(("Could not create directory: " + dirname).c_str());
    }
}

void change_directory(const std::string& dirname) {
    if (chdir(dirname.c_str()) == -1) {
        throw ChangeDirectoryException(("Could not change directory to: " + dirname).c_str());
    }
}