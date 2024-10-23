#pragma once

#include <filesystem>
#include <vector>
#include <string>

std::vector<std::string> getFilesInDirectory(const std::string& directoryPath) {
    std::vector<std::string> files;
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_regular_file()) {
            files.push_back(entry.path().filename().string());
        }
    }
    return files;
}

std::vector<std::string> getDirectoriesInDirectory(const std::string& directoryPath) {
    std::vector<std::string> directories;
    for (const auto& entry : std::filesystem::directory_iterator(directoryPath)) {
        if (entry.is_directory()) {
            directories.push_back(entry.path().filename().string());
        }
    }
    return directories;
}

std::vector<std::string> getFilesAndDirectories(const std::string& directoryPath) {
    std::vector<std::string> files = getFilesInDirectory(directoryPath);
    std::vector<std::string> directories = getDirectoriesInDirectory(directoryPath);
    std::vector<std::string> result(directories);
    result.insert(result.end(), files.begin(), files.end());
    return result;
}

std::string getCurrentWorkingDirectory() {
    return std::filesystem::current_path().string();
}