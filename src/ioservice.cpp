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



#include <ioservice.hpp>

//FIXME: Bad code
void IoService::info_(const boost::json::array &argv){

    boost::json::object json;
    boost::json::array array;


    try{


        if(argv.size() == 1){
            for(const auto & id:*onGetAllTorrentId()){
                array.push_back(*onInfo(id));
            }
        }
        else{
            for(auto it = argv.begin()+1;it!=argv.end();++it){
                auto id = it->get_int64();
                array.push_back(*onInfo(id));

            }


        }

        json["code"] = static_cast<int>(RESPONSE_CODE::CODE_OK);

    }catch(const std::exception &exp){
        json["code"] = static_cast<int>(RESPONSE_CODE::CODE_ERROR);
        json["message"] = exp.what();
    }



    json["torrent"] = array;

    std::cout << json << std::endl;

}

IoService::IoService(){

    boost::locale::generator gen;
    std::locale loc = gen("");
    std::locale::global(loc);
    std::cout.imbue(loc);
    std::cerr.imbue(loc);
}

void IoService::work(){

    std::flush(std::cout);

    std::string inputStr;

    std::getline(std::cin,inputStr);

    boost::json::array argv;


    try{
        argv = boost::json::parse(inputStr).as_array();
    }catch(const std::exception &exp){
        simpleResponse(exp.what(),RESPONSE_CODE::CODE_ERROR);
        return;
    }


    const int eccode = commandToInt(argv.at(0).as_string().c_str());


    switch (static_cast<COMMAND>(eccode)){

    case COMMAND::EXIT: onExit() ; break;
    case COMMAND::INFO: info_(argv); break;
    case COMMAND::ADD: onAddTorrent(argv.at(1).as_string().c_str()); break;
    case COMMAND::ADDMAGNET: onAddMagnetTorrent(argv.at(1).as_string().c_str()); break;
    case COMMAND::REMOVE: onRemoveTorrent(argv.at(1).to_number<int64_t>());break;

    default: simpleResponse("command not found",RESPONSE_CODE::CODE_ERROR); break;
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
