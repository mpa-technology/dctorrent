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

#include "TorrentManager.hpp"


TorrentManager* TorrentManager::torrent_;


TorrentManager::TorrentManager(TorrentManager::sessionPointType session){

    torrent_ = this;
    this->session_ = session;

}

void TorrentManager::addTorrent(const std::string &fileName, const std::string &savePath){

    if(!boost::filesystem::exists(fileName)){

        throw std::runtime_error("file no exists");
        return;
    }


    TorrentParam torrentParam;
    torrentParam.setFilePath(fileName);
    torrentParam.setSavePath( (savePath.empty() ? "." : savePath ) );

    torrent_->session_->addTorrent(std::move(torrentParam));


}

void TorrentManager::pauseTorrent(const int64_t id){
    verify_();
    torrent_->session_->getTorrent(id).pause();
}

void TorrentManager::pauseTorrentNode(const int64_t torrentId, const int64_t nodeId){
    verify_();
    torrent_->session_->getTorrent(torrentId).pause(nodeId);
}

void TorrentManager::removeTorrent(const int64_t id){
    verify_();

    try {
        torrent_->session_->removeTorrent(id);
    } catch (const std::exception &exp) {
       throw std::runtime_error(exp.what());
    }



}




void TorrentManager::verify_(){

    if(torrent_ == nullptr)//TODO: FIXME new msg
        //TODO: NEW EXP
        throw std::runtime_error("torrent not build");
    //TODO: NEW EXP
    if(torrent_->session_ == nullptr)
        throw std::runtime_error("session not set");
}
