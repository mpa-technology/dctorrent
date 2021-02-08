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


#include <Session.hpp>



SessionException::SessionException(const std::string &msg): msg_(msg){}



const char *SessionException::what() const noexcept{
    return msg_.c_str();
}




int64_t Session::findFreeId_(const int64_t &id){
    if(torrentFiles_.empty())
        return 0;

    for(auto& it : torrentFiles_)
        if(it.getId()==id){
            return findFreeId_(id+1);
        }

    return id;
}

TorrentFile Session::getTorrent(const int64_t id){

    for(const auto& it : torrentFiles_)
        if(it.getId() == id)
            return it;


    throw std::invalid_argument("id not found");
}

void Session::torrentUpdate(){

    for(auto &it : torrentFiles_)
        it.update();
}

std::list<TorrentFile> Session::getAllTorrent(){
    return torrentFiles_;
}

libtorrent::session &Session::session(){
    return session_;
}

void Session::addTorrentMagnet(TorrentParam &&tf){

    if(tf.isFile()){
        throw SessionException("wrong type of parmatir. tf==FILE");
    }



    auto th = session_.add_torrent(tf.params());



    const auto start = std::chrono::steady_clock::now();



    while (!th.status().has_metadata) {

       const auto elapsed = std::chrono::duration_cast<std::chrono::seconds>
            (std::chrono::steady_clock::now() - start).count();

       if(elapsed >= 25)
           throw SessionException("waiting for metadata >= 25");


    }

    torrentFiles_.push_back(th);

    torrentFiles_.back().setId(findFreeId_());



}

void Session::addTorrent(TorrentParam &&tf){


    if(tf.isMagnet()){
        throw SessionException("wrong type of parmatir. tf==MAGNET");
    }

    auto th = session_.add_torrent(tf.params());


    torrentFiles_.push_back(th);

    torrentFiles_.back().setId(findFreeId_());


}

void Session::removeTorrent(const TorrentFile &tf){
    session_.remove_torrent(tf.getNativeTorrentHandle());
    torrentFiles_.remove(tf);


}

void Session::removeTorrent(const int64_t id)
{

    for(const auto& it :  torrentFiles_)
        if(it.getId() == id){

            removeTorrent(it);
            return;
        }

    throw std::invalid_argument("id not found");
}

