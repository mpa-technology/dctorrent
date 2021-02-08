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



#include <IoService.hpp>


std::string IoService::getLine_(){
    std::string inputString;
    std::getline(std::cin,inputString);
    return inputString;
}

std::vector<std::string> IoService::parsingArgument_(const std::string &string){

    std::vector<std::string> argv;

    boost::json::array jarra = boost::json::parse(string).as_array();

    for(auto it : jarra){
        argv.push_back(it.as_string().c_str());

    }

    return argv;
}

Response IoService::commandExec_(const COMMAND command, const std::vector<std::string> &argv){

    if(!commandExist(command))
        throw IoServiceException("command not exist");

    switch (command){
    case COMMAND::EXIT:  onExit() ; return {}; break;
    case COMMAND::INFOT: return info_(argv); break;
    case COMMAND::ADDT: return addt_({argv.begin(),argv.end()});break;
    case COMMAND::ADDMAGNET: return addtm_({argv.begin(),argv.end()});break;
    case COMMAND::REMOVET: onRemoveTorrent(std::stoll(argv.at(0))); return {}; break;
    case COMMAND::ERROR_COMMAND: throw IoServiceException("error command"); break;
    case COMMAND::PAUSET: ;//TODO: ;

    }


    throw IoServiceException("error command");
}

Response IoService::info_(const std::vector<std::string> &argv){

    boost::json::object json;
    boost::json::array array;


    try{


        if(argv.empty()){
            for(const auto &it : TorrentInfo::getAllTorrentInfo()){
                array.push_back(it);
            }
        }
        else{
            for(auto it = argv.begin()+1;it!=argv.end();++it){
                const auto id = std::stoll(*it);
                array.push_back(TorrentInfo::getTorrentInfo(id));
            }


        }

        json["code"] = static_cast<int>(RESPONSE_CODE::CODE_OK);


    }catch(const std::exception &exp){
        simpleResponse(exp.what(),RESPONSE_CODE::CODE_OK);
        return {};
    }



    json["torrent"] = array;

    std::cout << json << std::endl;

    return {};
}

Response IoService::addt_(const std::vector<std::string> &argv){

    if(argv.empty())
        throw IoServiceException("argv empty");


    if(argv.size() > 1)
        onAddTorrent(argv.at(0),argv.at(1));
    else
        onAddTorrent(argv.at(0),{});

    return {};
}

Response IoService::addtm_(const std::vector<std::string> &argv)
{


    if(argv.empty())
        throw IoServiceException("argv empty");

    if(argv.size() > 1)
        onAddMagnetTorrent(argv.at(0),argv.at(1));
    else
        onAddMagnetTorrent(argv.at(0),{});

    simpleResponse("torrent add",RESPONSE_CODE::CODE_OK);

    return {};
}

IoService::IoService(){

    boost::locale::generator gen;
    std::locale loc = gen("");
    std::locale::global(loc);
    std::cout.imbue(loc);
    std::cerr.imbue(loc);

}

void IoService::work(){



    try{
        std::flush(std::cout);



        std::string inputStr = getLine_();


        const auto argv = parsingArgument_(inputStr);

        const auto eccode = static_cast<COMMAND>(commandToInt(argv.at(0)));

        const auto response = commandExec_(eccode,{argv.begin()+1,argv.end()});


        if(response.empty())
            simpleResponse(response);



    }catch(const std::exception &exp){
        simpleResponse(exp.what(),RESPONSE_CODE::CODE_ERROR);
    }

}

void IoService::simpleResponse(const std::string &msg, int code){

    boost::json::object obj;
    obj["code"] = code;
    obj["message"] = msg;

    std::cout << obj << '\n';
}

void IoService::simpleResponse(const std::string &msg, RESPONSE_CODE code)
{
    boost::json::object obj;
    obj["code"] = static_cast<int>(code);
    obj["message"] = msg;

    std::cout << obj << '\n';

}

void IoService::simpleResponse(const Response &response){
    simpleResponse(response.getMessage(),response.getResponseCode());
}


