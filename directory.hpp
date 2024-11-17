#pragma once

#include <sys/stat.h>
#include <string>

#include "customexcept.hpp"

void createDirectory(const std::string& dirname) {
    if (mkdir(dirname.c_str()) == -1) {
        throw CreateDirectoryException(("Could not create directory: " + dirname).c_str());
    }
}

void changeDirectory(const std::string& dirname) {
    if (chdir(dirname.c_str()) == -1) {
        throw ChangeDirectoryException(("Could not change directory to: " + dirname).c_str());
    }
}

void deleteDirectory(const std::string& dirname) {
    if (rmdir(dirname.c_str()) == -1) {
        throw DeleteDirectoryException(("Could not delete directory: " + dirname).c_str());
    }
}