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

#include <iostream>
#include <vector>
#include <string>

#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include <boost/signals2.hpp>
#include <boost/json.hpp>


#include <Utility.hpp>
#include <Session.hpp>
#include <TorrentFile.hpp>
#include <Respons.hpp>
#include <Command.hpp>
#include <TorrentInfo.hpp>
#include <TorrentManager.hpp>


class IoServiceException : public std::exception{


    std::string msg_;

public:


    IoServiceException(const std::string &msg);

    virtual  ~IoServiceException();

    virtual const char* what() const noexcept;

};



class IoService{


public:


    IoService();


    void work( );

    static void simpleResponse(const std::string &msg , int code);
    static void simpleResponse(const std::string &msg , RESPONSE_CODE code);
    static void simpleResponse(const Response &response);


    boost::signals2::signal<void()>onExit;
    boost::signals2::signal<void(const std::string& , const std::string&)>onAddTorrent;
    boost::signals2::signal<void(const std::string& , const std::string&)>onAddMagnetTorrent;
    boost::signals2::signal<void(const int64_t)>onRemoveTorrent;





private:


    std::string getLine_();

    std::vector<std::string> parsingArgument_( const std::string &string );

    Response commandExec_( const COMMAND command , const std::vector<std::string> &argv);


    Response info_(const std::vector<std::string> &argv);


    Response addt_(const std::vector<std::string>& argv);
    Response addtm_(const std::vector<std::string>& argv);




};

