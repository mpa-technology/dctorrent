#pragma once
#include <memory>
#include <boost/json.hpp>
#include <session.hpp>
#include <boost/filesystem.hpp>

class TorrentManager{
public:


    using sessionPointType = std::shared_ptr<Session>;
    using stringList = std::vector<std::string>;
    using jsonList = std::vector<boost::json::object>;

    TorrentManager(sessionPointType session);


    static void addTorrent(const std::string &fileName, const std::string &savePath){

        if(!boost::filesystem::exists(fileName)){

            throw std::runtime_error("file no exists");
            return;
        }


        TorrentParam torrentParam;
        torrentParam.setFilePath(fileName);
        torrentParam.setSavePath( (savePath.empty() ? "." : savePath ) );

        torrent_->session_->addTorrent(std::move(torrentParam));


}


private:
    static TorrentManager* torrent_;
    sessionPointType session_;


    static void verify_();



};
