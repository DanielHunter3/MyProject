#pragma once

#include <fstream>
#include <string>
#include <filesystem>
#include <array>
#include <format>

#include "customexcept.hpp"

namespace fs = std::filesystem;

class File {
public:
    File(const std::string filename) 
        : m_filename(filename) {
            if (!fs::exists(filename)) {
                throw FileNotFoundException(("File not found: " + filename).c_str());
            }
        }

    void writeFile(const std::string& string, std::ios_base::openmode mode = std::ios::out) {
        std::ofstream file(m_filename, mode);
        if (!file.is_open()) {
            throw FileWriteException(("Error opening file: " + m_filename).c_str());
        }
        file << string;
        file.close();
    }

    std::string readFile() {
        std::ifstream file(m_filename);
        std::string result, line;
        if (!file.is_open()) {
            throw FileReadException(("Error opening file: " + m_filename).c_str());
        }
        while (std::getline(file, line)) {
            result += line + "\n";
        }
        return result;
    }

    void renameFile(const std::string& filename) {
        fs::rename(m_filename, filename);
        m_filename = filename;
    }

    void copyFile(const std::string& dest) {
        fs::copy(m_filename, dest);
    }

    std::string returnPermissions(const fs::path& path) {
    fs::perms p = fs::status(path).permissions();
    return std::format("Permissions for {}: {}{}{}{}{}{}{}{}{}: \n", path,
              ((p & fs::perms::owner_read) != fs::perms::none ? "r" : "-"),
              ((p & fs::perms::owner_write) != fs::perms::none ? "w" : "-"),
              ((p & fs::perms::owner_exec) != fs::perms::none ? "x" : "-"),
              ((p & fs::perms::group_read) != fs::perms::none ? "r" : "-"),
              ((p & fs::perms::group_write) != fs::perms::none ? "w" : "-"),
              ((p & fs::perms::group_exec) != fs::perms::none ? "x" : "-"),
              ((p & fs::perms::others_read) != fs::perms::none ? "r" : "-"),
              ((p & fs::perms::others_write) != fs::perms::none ? "w" : "-"),
              ((p & fs::perms::others_exec) != fs::perms::none ? "x" : "-")
              );
    }

    void setPermissions(const fs::perms& permissions) {
        fs::permissions(m_filename, permissions);
    }
private:
    std::string m_filename;
};

void deleteFile(const std::string& path) {
    if (!fs::remove(path)) {
        throw FileDeleteException(("Error deleting file: " + path).c_str());
    }
}

void createFile(const std::string& path) {
    if (fs::exists(path)) {
        throw FileCreateException(("File have already created: " + path).c_str());
    }
    std::ofstream file(path);
    if (!file.is_open()) {
        throw FileCreateException(("Error opening file: " + path).c_str());
    }
    file.close();
}
