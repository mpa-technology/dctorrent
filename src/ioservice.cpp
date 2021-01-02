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


std::vector<std::string> IoService::getComand_(const std::string &line){

    std::vector<std::string>list;

    boost::split(list,line,boost::is_any_of(" "));

    return list;
}

void IoService::cm_info(TorrentFile &torrentFile){

    std::cout << torrentFile.name() << '\t' <<   (!torrentFile.isFinished()?"[in process]":"[finish]") << ' ' << torrentFile.totalProgress()  << '\n';

    for( const auto& it : torrentFile.getNode()){

        const auto progress = std::ceil( 100.0/static_cast<float>(it.size)*static_cast<float>(it.progress));
        std::string priority = !it.priority ? "[pause]" : "";


        std::cout << it.id <<  ") " << priority << it.name  <<  '\t' << progress << '%' << '\n';
    }

}

void IoService::cm_pause(TorrentFile &torrentFile, const int &id){

    try {
        torrentFile.pause(id);
        std::cout << "torrent file pause" << '\n';
    }  catch (const std::out_of_range& exp) {
        std::cerr << "id: " << id << "not found" << '\n';

    }


}

void IoService::cm_resume(TorrentFile &torrentFile, const int &id){

    try {
        torrentFile.resume(id);
        std::cout << "torrent file pause" << '\n';
    }  catch (const std::out_of_range& exp) {
        std::cerr << "id: " << id << "not found" << '\n';

    }


}

IoService::IoService(){

    boost::locale::generator gen;
    std::locale loc = gen("");
    std::locale::global(loc);
    std::cout.imbue(loc);
    std::cerr.imbue(loc);
}

bool IoService::work(TorrentFile &torrentFile){

    std::flush(std::cout);


    std::string inputStr;

    std::getline(std::cin,inputStr);

    const auto commnd = getComand_(inputStr);


    if(commnd.empty())
        return true;


    if(std::find(comands_.begin(), comands_.end(), comands_.at(0)) == comands_.end()){
        std::cerr << "comand: " << commnd.at(0) << " not found" << '\n';
        return true;
    }


    if(commnd.at(0)=="exit")
        return false;

    if(commnd.at(0)=="info"){
        cm_info(torrentFile);
        return true;
    }

    if(commnd.at(0) == "pause" && commnd.size() == 2 ){
        cm_pause(torrentFile,std::stoi(commnd.at(1)));
        return true;
    }


    if(commnd.at(0) == "resume" && commnd.size() == 2 ){
        cm_resume(torrentFile,std::stoi(commnd.at(1)));
        return true;
    }



    std::cerr << "comand error" << '\n';


    return true;
}
