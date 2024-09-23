#include "../include/ArgoLogger.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <mutex>

namespace ArgoDraft {
    Logger::Logger() {
        this->fileName = "ArgoLogger.log";
    }

    Logger::Logger(
        const std::string &fileName
    ) {
        this->fileName = fileName;
    }

    void Logger::LogMessage(
        const char *message,
        const int level
    ) const {
        if (this->CanConsoleLog(level)) {
            std::cout << "Logging Message: " << std::endl;
            std::cout << message << std::endl;
        }

        if (level < this->fileLogLevel) {
            return;
        }

        WriteToLogFile(message, level);
    }

    void Logger::SetFileName(
        const std::string &fileName
    ) {
        this->fileName = fileName;
    }

    void Logger::SetFileLogLevel(const int fileLogLevel) {
        this->fileLogLevel = fileLogLevel;
    }

    void Logger::SetConsoleLogLevel(const int consoleLogLevel) {
       this->consoleLogLevel = consoleLogLevel;
    }

    void Logger::CreateLogFile() const {
        if (this->CanConsoleLog(LogLevel::DEBUG)) {
            std::cout << "Creating Log File..." << std::endl;
            std::cout << "Log File: " << this->fileName << std::endl;
        }

        // check if the file exists
        if (std::filesystem::exists(this->fileName)) {
            if (this->CanConsoleLog(LogLevel::DEBUG)) {
                std::cout << "Log File already exists." << std::endl;
            }
        } else {
            if (this->CanConsoleLog(LogLevel::DEBUG)) {
                std::cout << "Log File does not exist." << std::endl;
            }

            std::ofstream logFile(this->fileName);
            logFile.close();
        }
    }

    void Logger::WriteToLogFile(
        const char *message,
        const int level
    ) const {
        if (this->CanConsoleLog(level)) {
            std::cout << "Writing to Log File..." << std::endl;
            std::cout << "Log File: " << this->fileName << std::endl;
            std::cout << "Message: " << message << std::endl;
        }

        if (!this->CanFileLog(level)) {
            return;
        }

        // Check if the file exists
        if (!std::filesystem::exists(this->fileName)) {
            CreateLogFile();
        }

        // Check if the file can be written to
        if (!std::filesystem::is_regular_file(this->fileName)) {
            if (this->CanConsoleLog(LogLevel::ERROR)) {
                std::cerr << "Log file can not be written" << std::endl;
            }

            return;
        }

        // Check if the file can be opened
        std::ofstream logFile(this->fileName, std::ios_base::app);
        if (!logFile.is_open()) {
            if (this->CanConsoleLog(LogLevel::ERROR)) {
                std::cerr << "Log file can not be opened" << std::endl;
            }

            return;
        }

        // Write the message to the log file
        logFile << message << std::endl;
        logFile.close();
    }

    bool Logger::CanConsoleLog(const int level) const {
        return (this->consoleLogLevel > LogLevel::NONE) && (level >= this->consoleLogLevel);
    }

    bool Logger::CanFileLog(const int level) const {
        return (this->fileLogLevel > LogLevel::NONE) && (level >= this->fileLogLevel);
    }
}
