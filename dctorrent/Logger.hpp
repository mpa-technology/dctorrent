#pragma once
#include <iostream>
#include <chrono>


class Logger{
    //TODO: FIX
    std::ostream& warringStream_;
    void sendWaring_(const std::string& message);

public:



    enum MESSAGE_TYPE{
    WARRING,
    ERROR,
    DEBUG
    };

    Logger();



    void sendMessage(const std::string& message , const MESSAGE_TYPE& msgType);



};

