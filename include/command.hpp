#pragma once

#include <string>

enum class COMMAND : int{
    EXIT,
    INFO,
    ADD,
    ERROR_COMMAND

};




constexpr int commandToInt( const std::string_view sv){

    if(sv == "EXIT" || sv=="exit")
        return static_cast<int>(COMMAND::EXIT);

    if(sv == "INFO" || sv=="info")
        return static_cast<int>(COMMAND::INFO);

    if(sv == "ADD" || sv=="add")
        return static_cast<int>(COMMAND::ADD);

    return static_cast<int>(COMMAND::ERROR_COMMAND);
}
