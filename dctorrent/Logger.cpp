#include "Logger.hpp"

void Logger::sendWaring_(const std::string &message){
    std::cout << "[WARRING]" << "" << message << std::endl;
}

Logger::Logger() : warringStream_(std::cout){

}

void Logger::sendMessage(const std::string &message, const Logger::MESSAGE_TYPE &msgType){

    switch (msgType) {
    case WARRING:sendWaring_(message);break;
    case DEBUG:sendWaring_(message);break;
    case ERROR:sendWaring_(message);break;
    }



}

