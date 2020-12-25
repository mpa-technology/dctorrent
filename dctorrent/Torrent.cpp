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



#include "Torrent.hpp"
#include <libtorrent/file_pool.hpp>

size_t Torrent::id() const
{
    return id_;
}


size_t Torrent::status() const
{
    return status_;
}

lt::torrent_handle Torrent::getTorrentHandle() const
{
    return torrentHandle_;
}

Torrent::Torrent(libtorrent::torrent_handle torrentHandle) : torrentHandle_(torrentHandle) , status_(0){
    id_ = torrentHandle_.id();

    for(auto it : torrentHandle_.torrent_file()->files()){
        TorrentFile tf;
        tf.setName(it.filename());
        tf.setSize(it.size);
        tf.setId(it.offset);
        tf.setId(torrentFiles_.size());
        torrentFiles_.push_back(tf);
    }

    std::vector<float>fileProgress;
    torrentHandle_.file_progress(fileProgress);

    status_ = 1;




}

void Torrent::update(){

     status_ = torrentHandle_.is_paused() == true ? TORRENT_STOP : TORRENT_RUN;



    std::vector<std::int64_t>fileProgress;
    torrentHandle_.file_progress(fileProgress);


    for ( size_t i = 0;i != fileProgress.size(); ++i ){
        torrentFiles_.at(i).setProgress(fileProgress.at(i));

    }


    for ( size_t i = 0;i != torrentFiles_.size(); ++i ){
        torrentFiles_.at(i).setStatus(torrentHandle_.file_priority(i) == 0 ? TORRENT_STOP : TORRENT_RUN);
    }





}

std::string Torrent::name() const{
    return  torrentHandle_.name();
}

float Torrent::progress() const{
    return std::round(( (torrentHandle_.status().progress)*10)*100)/100;
}

bool Torrent::isFinished() const{
    return  torrentHandle_.is_finished();
}

void Torrent::resumeAll(){
    torrentHandle_.resume();
}

void Torrent::pause(const size_t &fid){

    torrentHandle_.file_priority(fid,0);
}

void Torrent::resume(const size_t &fid){
    torrentHandle_.file_priority(fid,4);
}

void Torrent::pauseAll(){
    torrentHandle_.pause();

}

std::vector<TorrentFile> Torrent::getFiles() const{

    return torrentFiles_;
}
