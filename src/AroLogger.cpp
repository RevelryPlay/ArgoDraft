#include "../include/ArgoLogger.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>

namespace ArgoDraft {
    void Logger::LogMessage(
        const char *message,
        const char *fileName,
        const bool console
    ) {
        if (console) {
            std::cout << "Logging Message: " << std::endl;
            std::cout << message << std::endl;
        }

        CreateLogFile(fileName, console);
        WriteToLogFile(message, fileName, console);
    }

    void Logger::CreateLogFile(const char *fileName, const bool console) {
        if (console) {
            std::cout << "Creating Log File..." << std::endl;
            std::cout << "Log File: " << fileName << std::endl;
        }

        // check if the file exists
        if (std::filesystem::exists(fileName)) {
            if (console) {
                std::cout << "Log File already exists." << std::endl;
                return;
            }
        }
        else {
            if (console) {
                std::cout << "Log File does not exist." << std::endl;
            }

            std::ofstream logFile(fileName);
            logFile.close();
        }
    }

    void Logger::WriteToLogFile(
        const char *message,
        const char *fileName,
        const bool console
    ) {
        if (console) {
            std::cout << "Writing to Log File..." << std::endl;
            std::cout << "Log File: " << fileName << std::endl;
            std::cout << "Message: " << message << std::endl;
        }

        // Write the message to the log file
        std::ofstream logFile(fileName, std::ios_base::app);
        logFile << message << std::endl;
        logFile.close();
    }
}
