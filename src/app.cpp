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

#include <app.hpp>

App::App(int argc, char **argv){


    for(int i = 0 ; i != argc; ++i)
        arguments_.push_back(argv[i]);




    ioService_ = std::make_unique<IoService>();

    ioService_->onExit.connect(std::bind(&App::onExit_,this));
    ioService_->onAddTorrent.connect(std::bind(&App::onAddTorrent_,this,std::placeholders::_1));
    ioService_->onAddMagnetTorrent.connect(std::bind(&App::onAddMagnetTorrent_,this,std::placeholders::_1));
    ioService_->onRemoveTorrent.connect(std::bind(&App::onRemoveTorrent_,this,std::placeholders::_1));
    ioService_->onInfo.connect(std::bind(&App::onInfo_,this,std::placeholders::_1));
    ioService_->onGetAllTorrentId.connect(std::bind(&App::onGetAllTorrentId,this));


    flags_.run = true;
}




void App::onExit_(){
    flags_.run = false;
}


void App::onAddTorrent_(const std::string &fileName)
{

    if(!boost::filesystem::exists(fileName)){
        ioService_->simpleResponse("no exists",RESPONSE_CODE::CODE_ERROR);
        return;
    }


    TorrentParam torrentParam;
    torrentParam.setFilePath(fileName);
    torrentParam.setSavePath(std::string("."));
    session_->addTorrent(std::move(torrentParam));



    ioService_->simpleResponse("torrent add",RESPONSE_CODE::CODE_OK);

}

void App::onAddMagnetTorrent_(const std::string &url){

    TorrentParam torrentParam;
    torrentParam.setMagnet(url);
    torrentParam.setSavePath(std::string("."));


    session_->addTorrentMagnet(std::move(torrentParam));
    ioService_->simpleResponse("torrent add",RESPONSE_CODE::CODE_OK);
}

void App::onRemoveTorrent_(const int64_t id){


    try{
        session_->removeTorrent(id);
        ioService_->simpleResponse("torrent remove",RESPONSE_CODE::CODE_OK);

    }catch(...){
        ioService_->simpleResponse("id not found",RESPONSE_CODE::CODE_ERROR);
    }


}

boost::json::object App::onInfo_(const int64_t id)
{
    return session_->getTorrent(id).json();
}

std::vector<int64_t> App::onGetAllTorrentId(){

    std::vector<int64_t>id;

    for(const auto &it : session_->getAllTorrent())
        id.push_back(it.getId());

    return id;
}




int App::run(){

    session_ = std::make_unique<Session>();


    ioService_->simpleResponse("start",RESPONSE_CODE::START_OK);


    while (flags_.run) {

        session_->torrentUpdate();

        ioService_->work();
    }


    ioService_->simpleResponse("exit",RESPONSE_CODE::EXIT_OK);



    return EXIT_SUCCESS;
}
