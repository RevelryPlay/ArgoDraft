#include "../include/ArgoLogger.hpp"

namespace ArgoDraft {
    Logger::Logger( ) { fileName = "ArgoLogger.log"; }

    Logger::Logger( const std::string &fileName ) { this->fileName = fileName; }

    void Logger::LogMessage( const char *message, const int level ) const {

        if ( message == nullptr || std::strlen( message ) == 0 ) {
            return;
        }

        if ( !CanConsoleLog( level ) && !CanFileLog( level ) ) {
            return;
        }

        if ( std::strlen( message ) > maxMessageSize ) {
            if ( CanConsoleLog( LogLevel::DEBUG ) ) {
                std::cout << "Message is too long." << std::endl;
                std::cout << "Current Length: " << std::strlen( message ) << " Max length: " << maxMessageSize
                          << std::endl;
            }

            // Log message is too long
            auto splitMessages = SplitMessage( message );
            for ( const auto &splitMessage : splitMessages ) {
                LogMessage( splitMessage.c_str( ), level );
            }

            return;
        }

        if ( CanConsoleLog( level ) ) {
            if ( CanConsoleLog( LogLevel::DEBUG ) ) {
                std::cout << "Logging Message: " << std::endl;
            }

            std::cout << message << std::endl;
        }

        if ( level < fileLogLevel ) {
            return;
        }

        WriteToLogFile( message, level );
    }

    void Logger::SetFileName( const std::string &fileName ) { this->fileName = fileName; }
    void Logger::SetFileLogLevel( const int fileLogLevel ) { this->fileLogLevel = fileLogLevel; }
    void Logger::SetConsoleLogLevel( const int consoleLogLevel ) { this->consoleLogLevel = consoleLogLevel; }
    void Logger::SetMaxMessageSize( const int maxMessageSize ) { this->maxMessageSize = maxMessageSize; }

    void Logger::CreateLogFile( ) const {
        if ( CanConsoleLog( LogLevel::DEBUG ) ) {
            std::cout << "Creating Log File..." << std::endl;
            std::cout << "Log File: " << fileName << std::endl;
        }

        // check if the file exists
        if ( std::filesystem::exists( fileName ) ) {
            if ( CanConsoleLog( LogLevel::DEBUG ) ) {
                std::cout << "Log File already exists." << std::endl;
            }
        } else {
            if ( CanConsoleLog( LogLevel::DEBUG ) ) {
                std::cout << "Log File does not exist." << std::endl;
            }

            std::ofstream logFile( fileName );
            logFile.close( );
        }
    }

    void Logger::WriteToLogFile( const char *message, const int level ) const {
        if ( CanConsoleLog( LogLevel::DEBUG ) ) {
            std::cout << "Writing to Log File..." << std::endl;
            std::cout << "Log File: " << fileName << std::endl;
            std::cout << "Message: " << message << std::endl;
        }

        if ( !CanFileLog( level ) ) {
            return;
        }

        // Check if the file exists
        if ( !std::filesystem::exists( fileName ) ) {
            CreateLogFile( );
        }

        // Check if the file can be written to
        if ( !std::filesystem::is_regular_file( fileName ) ) {
            if ( CanConsoleLog( LogLevel::ERROR ) ) {
                std::cerr << "Log file can not be written" << std::endl;
            }

            return;
        }

        // Check if the file can be opened
        std::ofstream logFile( fileName, std::ios_base::app );
        if ( !logFile.is_open( ) ) {
            if ( CanConsoleLog( LogLevel::ERROR ) ) {
                std::cerr << "Log file can not be opened" << std::endl;
            }

            return;
        }

        // Write the message to the log file
        logFile << GetLogLineMetadata( level ) << message << std::endl;
        logFile.close( );
    }

    std::string Logger::GetLogLineMetadata( const int level ) const {
        std::string logLineMetadata;

        auto        now   = std::chrono::system_clock::now( );
        std::time_t now_c = std::chrono::system_clock::to_time_t( now );

        logLineMetadata += GetLogLevelString( level );
        logLineMetadata += " ";
        logLineMetadata += std::format( "{0:%FT%TZ}", std::chrono::system_clock::from_time_t( now_c ) );
        logLineMetadata += " ";

        return logLineMetadata;
    }

    std::string Logger::GetLogLevelString( const int level ) const {
        std::string logLevelString;
        switch ( level ) {
            case LogLevel::DEBUG:
                logLevelString = "DEBUG";
                break;
            case LogLevel::INFO:
                logLevelString = "INFO";
                break;
            case LogLevel::WARNING:
                logLevelString = "WARNING";
                break;
            case LogLevel::ERROR:
                logLevelString = "ERROR";
                break;
            case LogLevel::CRITICAL:
                logLevelString = "CRITICAL";
                break;
            default:
                logLevelString = "NONE";
                break;
        }

        return logLevelString;
    }

    bool Logger::CanConsoleLog( const int level ) const {
        return ( consoleLogLevel > LogLevel::NONE ) && ( level >= consoleLogLevel );
    }

    bool Logger::CanFileLog( const int level ) const {
        return ( fileLogLevel > LogLevel::NONE ) && ( level >= fileLogLevel );
    }

    std::vector< std::string > Logger::SplitMessage( const char *message ) const {
        // Split the message into smaller messages based on the max message size
        // Try to split the message at a space or newline character if possible
        std::vector< std::string > splitMessages;
        std::string                messageString( message );

        while ( messageString.length( ) > maxMessageSize ) {
            std::size_t splitIndex = messageString.find_last_of( " ", maxMessageSize );
            if ( splitIndex == std::string::npos ) {
                splitIndex = maxMessageSize;
            }

            splitMessages.push_back( messageString.substr( 0, splitIndex ) );
            messageString = messageString.substr( splitIndex + 1 );
        }

        splitMessages.push_back( messageString );
        return splitMessages;
    }
} // namespace ArgoDraft
