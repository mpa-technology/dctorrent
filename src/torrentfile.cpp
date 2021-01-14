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

#include <torrentfile.hpp>



TorrentFile::TorrentFile(libtorrent::torrent_handle th) : torrentHandle_(th){

    auto files = torrentHandle_.torrent_file()->files();

    torrentHandle_.torrent_file()->files().file_range();

    for( auto it : files.file_range()){

        const auto inti = static_cast<int>(it);

        TorrentNode node;
        node.id = inti;

        node.name = files.file_name(it).to_string();
        node.size = files.file_size(it);
        node.index = it;

        node.progress = torrentHandle_.file_progress().at(static_cast<size_t>(inti));

        torrentNodes_.push_back(node);
    }



}

void TorrentFile::pause(const int &id){
    torrentHandle_.file_priority(torrentNodes_.at(static_cast<size_t>(id)).index,lt::dont_download);

}

void TorrentFile::resume(const int &id){
    torrentHandle_.file_priority(torrentNodes_.at(static_cast<size_t>(id)).index,lt::default_priority);
}

std::vector<TorrentNode> TorrentFile::getNode() const{


    return torrentNodes_;
}

void TorrentFile::update(){
    auto files = torrentHandle_.torrent_file()->files();

    for( auto& it : torrentNodes_){


        it.name = files.file_name(it.index).to_string();
        it.size = files.file_size(it.index);

        it.priority = toTorrentPriority(torrentHandle_.file_priority(it.index));

        it.progress = torrentHandle_.file_progress().at(static_cast<size_t>(it.id));


    }

}

bool TorrentFile::isFinished() const{
    return torrentHandle_.status().is_finished;
}

std::string TorrentFile::name() const{
    return torrentHandle_.status().name;
}

nlohmann::json TorrentFile::json() const{
    nlohmann::json json{ {"name",name()}, {"id",id_}};
    std::vector<nlohmann::json> tlist;

    for(auto& it : getNode()){

        nlohmann::json obj{
            {"id",it.id},
            {"name",it.name},
            {"priority",it.priority},
            {"progress",it.progress},
            {"size",it.size}

        };


        tlist.push_back(obj);


    }



    json["torrent"]=tlist;


    return json;
}

bool TorrentFile::operator==(const TorrentFile &file) const{
    return id_ == file.id_ && hash() == file.hash();
}

std::string TorrentFile::hash() const{

    return  torrentHandle_.info_hash().to_string();
}

libtorrent::torrent_handle TorrentFile::getNativeTorrentHandle() const{
    return torrentHandle_;
}

int64_t TorrentFile::getId() const
{
    return id_;
}

void TorrentFile::setId(const int64_t &id)
{
    id_ = id;
}

TorrentFile::TorrentFile(){}

float TorrentFile::totalProgress() const{
    return  torrentHandle_.status().progress;
}
