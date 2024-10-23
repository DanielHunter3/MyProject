#pragma once

#include <exception>
#include <string>

class FileNotFoundException : public std::exception {
private:
    const char* message;
public:
    FileNotFoundException(const char* message) : message(message) {}
    const char* what() const noexcept override {
        return message;
    }
};

class FileWriteException : public std::exception {
private:
    const char* message;
public:
    FileWriteException(const char* message) : message(message) {}
    const char* what() const noexcept override {
        return message;
    }
};

class FileReadException : public std::exception {
private:
    const char* message;
public:
    FileReadException(const char* message) : message(message) {}
    const char* what() const noexcept override {
        return message;
    }
};

class CreateDirectoryException : public std::exception {
private:
    const char* message;
public:
    CreateDirectoryException(const char* message) : message(message) {}
    const char* what() const noexcept override {
        return message;
    }
};

class ChangeDirectoryException : public std::exception {
private:
    const char* message;
public:
    ChangeDirectoryException(const char* message) : message(message) {}
    const char* what() const noexcept override {
        return message;
    }
};