#pragma once
#include <memory>
#include <boost/json.hpp>
#include <session.hpp>



class TorrentInfo{
public:


    using sessionPointType = std::shared_ptr<Session>;
    using stringList = std::vector<std::string>;

    TorrentInfo(sessionPointType session);

    static stringList getTorrentFileNames();


private:
    static TorrentInfo* torrent_;
    sessionPointType session_;



};

