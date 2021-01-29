#include "TorrentInfo.hpp"

TorrentInfo* TorrentInfo::torrent_;

TorrentInfo::TorrentInfo(TorrentInfo::sessionPointType session):session_(session){
    torrent_ = this;
}

TorrentInfo::stringList TorrentInfo::getTorrentFileNames(){
    stringList result;

    auto list  = torrent_->session_->getAllTorrent();

    for(auto it : list){
        result.push_back(it.name());
    }


    return result;
}
