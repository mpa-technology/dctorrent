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
void IoService::info_(const std::list<TorrentFile> &torrentFiles,const std::vector<std::string> &argv){

    nlohmann::json json{ {"code",RESPONSE_CODE::CODE_OK} };

    std::vector<int64_t>idList;

    if(argv.size()==1){
        for(const auto & it : torrentFiles)
            idList.push_back(it.getId());
    }else
        for(auto it = argv.begin()+1;it!=argv.end();++it)
            idList.push_back(std::stoll(*it));



    for(const auto &tf:torrentFiles){

        for(const auto &id : idList)
            if(id == tf.getId()){
                json["torrent"] += tf.json();
                break;
            }


    }




//    if(argv.size() == 1){






//        for(auto& it : torrentFiles)
//            json["torrent"] += it.json();

//    }

//    for(auto it = argv.begin()+1;it!=argv.end();++it){
//        auto id = std::stoll(*it);
//        for(auto f : torrentFiles)
//            if(f.getId()==id)
//

//    }


    std::cout << json << std::endl;

}

IoService::IoService(){

    boost::locale::generator gen;
    std::locale loc = gen("");
    std::locale::global(loc);
    std::cout.imbue(loc);
    std::cerr.imbue(loc);
}

void IoService::work(const std::list<TorrentFile>& torrentFiles){

    std::flush(std::cout);

    std::string inputStr;

    std::getline(std::cin,inputStr);

    std::vector<std::string> argv;

    try{
        auto resp = nlohmann::json::parse(inputStr);
        argv = resp.get<std::vector<std::string>>();
    }catch(const std::exception &exp){
        std::cout << nlohmann::json{ {"code", RESPONSE_CODE::CODE_ERROR} , {"message" , exp.what() } } << '\n';
        return;
    }


    const int eccode = commandToInt(argv.at(0));


    switch (static_cast<COMMAND>(eccode)){

    case COMMAND::EXIT: onExit() ; break;
    case COMMAND::INFO: info_(torrentFiles,argv); break;
    case COMMAND::ADD: onAddTorrent(argv.at(1)); break;
    case COMMAND::REMOVE: onRemoveTorrent(std::stoll(argv.at(1)));break;

        //FIXME: rename
    default: std::cout << nlohmann::json{ {"code", RESPONSE_CODE::CODE_ERROR} , {"message" , "COMMAND NOT" } } << '\n'; break;
    }







}
