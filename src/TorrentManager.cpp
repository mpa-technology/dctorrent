#include "TorrentManager.hpp"


TorrentManager* TorrentManager::torrent_;


TorrentManager::TorrentManager(TorrentManager::sessionPointType session){

    torrent_ = this;
    this->session_ = session;

}




void TorrentManager::verify_(){

    if(torrent_ == nullptr)//TODO: FIXME new msg
        //TODO: NEW EXP
        throw std::runtime_error("torrent not build");
    //TODO: NEW EXP
    if(torrent_->session_ == nullptr)
        throw std::runtime_error("session not set");
}
