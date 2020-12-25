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

#include "App.hpp"






//TODO: move to inputOutputService
void printGetInfo ( const Torrent& torrent){

    nlohmann::json json;
    std::vector<nlohmann::json>objl;

    for(auto it:torrent.getFiles()){
        nlohmann::json obj;


        std::string status;
        switch (it.status()) {
        case TORRENT_RUN:status = "run";break;
        case TORRENT_STOP:status = "stop";break;
        }

        obj = {
            {"fileName",it.name()},
            {"fileStatus",status},
            {"fileId",it.id()},
            {"fileSize",it.size()},
            {"progress",it.progress()
            }};

        objl.push_back(obj);

    }

    std::string status;
    switch (torrent.status()) {
    case TORRENT_RUN:status = "run";break;
    case TORRENT_STOP:status = "stop";break;
    }


    nlohmann::json toi = {
        {"torrentName",torrent.name()},
        {"torrentStatus",status},
        {"torrentId",torrent.id()},
        {"fileCount",torrent.getFiles().size()},
        {"isFinished",torrent.isFinished()},
        {"progress", torrent.progress()},
        {"torrents",objl}
    };

    json["torrent"] = toi;




    std::cout << json << std::endl;

}

std::string getString(){

    std::string input;
    std::getline(std::cin, input);
    return input;
}

App::App(const int &argc, char **argv){

    apppath_ = argv[0];

    for(int i = 1;i!=argc;++i)
        arguments_.push_back(argv[i]);


    isRun_ = false;

}

void App::command( const std::vector<std::string>& command){

    if(command[0]=="NULL"){
        std::cout << nlohmann::json({"dctorrent",{"error",404,"command not foind",command[0]}})<<std::endl;
        return;
    }

    if( command.at(0) == "info"){
        torrentService_.update();
        for(const auto& it:torrentService_.torrentHandle()){
            printGetInfo(it);
        }
    }

    if( command.at(0) == "remove"){
        torrentService_.removeTorrent(0);
    }

    if( command.at(0) == "exit"){
        isRun_ = false;
        return;
    }

    if( command.at(0) == "pause"){

        if(command.size() == 1){
            torrentService_.pauseAll();
        }


        auto tid = std::stoul(command.at(1));
        auto tfid = std::stoul(command.at(2));
        torrentService_.pause(tid,tfid);



    }

    if( command.at(0) == "resume"){

        if(command.size() == 1){
            torrentService_.resumeAll();
        }


        auto tid = std::stoul(command.at(1));
        auto tfid = std::stoul(command.at(2));
        torrentService_.resume(tid,tfid);


    }

    if( command.at(0) == "add"){
        auto path = command.at(1);
        torrentService_.addTorrent(path,{});
        std::cout << nlohmann::json({"dctorrent",{"status","ok"}})<<std::endl;
    }


}

int App::run(){

    for(const auto&it : arguments_)
        torrentService_.addTorrent(it,{});

    torrentService_.start();

    isRun_ = true;


    while (isRun_) {
        command(inputOutputService_.getCommand());
    }

    return EXIT_SUCCESS;
}
