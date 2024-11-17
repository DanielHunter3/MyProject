#pragma once

#include <exception>
#include <string>

class FileNotFoundException : public std::exception {
private:
    const char* m_message;
public:
    FileNotFoundException(const char* message) : m_message(message) {}
    const char* what() const noexcept override {
        return m_message;
    }
};

class FileWriteException : public std::exception {
private:
    const char* m_message;
public:
    FileWriteException(const char* message) : m_message(message) {}
    const char* what() const noexcept override {
        return m_message;
    }
};

class FileReadException : public std::exception {
public:
    FileReadException(const char* message) : m_message(message) {}
    const char* what() const noexcept override {
        return m_message;
    }
private:
    const char* m_message;
};

class FileDeleteException : public std::exception {
public:
    FileDeleteException(const char* message) : m_message(message) {}
    const char* what() const noexcept override {
        return m_message;
    }
private:
    const char* m_message;
};

class CreateDirectoryException : public std::exception {
public:
    CreateDirectoryException(const char* message) : m_message(message) {}
    const char* what() const noexcept override {
        return m_message;
    }
private:
    const char* m_message;
};

class ChangeDirectoryException : public std::exception {
public:
    ChangeDirectoryException(const char* message) : m_message(message) {}
    const char* what() const noexcept override {
        return m_message;
    }
private:
    const char* m_message;
};

class FileCreateException : public std::exception {
public:
    FileCreateException(const char* message) : m_message(message) {}
    const char* what() const noexcept override {
        return m_message;
    }
private:
    const char* m_message;
};

class DeleteDirectoryException : public std::exception {
public:
    DeleteDirectoryException(const char* message) : m_message(message) {}
    const char* what() const noexcept override {
        return m_message;
    }
private:
    const char* m_message;
};