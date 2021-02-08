#include <TorrentInfo.hpp>

TorrentInfo* TorrentInfo::torrent_ = nullptr;

TorrentInfo::TorrentInfo(TorrentInfo::sessionPointType session):session_(session){
    torrent_ = this;
}

TorrentInfo::stringList TorrentInfo::getTorrentFileNames(){

    verify_();

    stringList result;

    auto list  = torrent_->session_->getAllTorrent();

    for( const auto &it : list){
        result.push_back(it.name());
    }


    return result;
}

boost::json::object TorrentInfo::getTorrentInfo(const int64_t id){
    verify_();

    return torrent_->session_->getTorrent(id).json();
}

TorrentInfo::jsonList TorrentInfo::getAllTorrentInfo(){
    verify_();

    jsonList result;

    for(const auto & it : torrent_->session_->getAllTorrent())
        result.push_back(it.json());


    return result;
}

void TorrentInfo::verify_(){

    if(torrent_ == nullptr)//TODO: FIXME new msg
        throw TorrentInfoException("torrent not build");

    if(torrent_->session_ == nullptr)
        throw TorrentInfoException("session not set");

}
