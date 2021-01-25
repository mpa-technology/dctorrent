/*
 * Copyright (c) 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of mosquitto nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */



#pragma once

#include <string>



class CommandException : public std::exception{


    std::string msg_;

public:


    CommandException(const std::string &msg);



    virtual  ~CommandException();


    virtual const char* what() const noexcept;


};


enum class COMMAND : int{
    EXIT,
    INFOT,
    ADDT,
    ADDMAGNET,
    REMOVET,
    ERROR_COMMAND

};



std::string toCommand(const int var);


constexpr int commandToInt( const std::string_view sv){

    if(sv == "EXIT" || sv=="exit")
        return static_cast<int>(COMMAND::EXIT);

    if(sv == "INFOT" || sv=="infot")
        return static_cast<int>(COMMAND::INFOT);

    if(sv == "ADDT" || sv=="addt")
        return static_cast<int>(COMMAND::ADDT);

    if(sv == "REMOVET" || sv=="removet")
        return static_cast<int>(COMMAND::REMOVET);

    if(sv == "ADDTM" || sv=="addtm")
        return static_cast<int>(COMMAND::ADDMAGNET);


    return static_cast<int>(COMMAND::ERROR_COMMAND);
}

constexpr bool commandExist(const COMMAND command){

    switch (command) {
    case COMMAND::EXIT:
    case COMMAND::INFOT:
    case COMMAND::ADDT:
    case COMMAND::REMOVET:
    case COMMAND::ADDMAGNET:
    case COMMAND::ERROR_COMMAND:return true;
    }

    return false;
}


