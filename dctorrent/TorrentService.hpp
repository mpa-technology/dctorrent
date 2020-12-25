/*  SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#pragma once
#include "Session.hpp"
#include <thread>


class TorrentService{


    Session session_;
    std::vector<Torrent>torrentHandle_;
    bool appIsRun_;
    std::thread thread_;

    void updateTorrent_();


public:


    TorrentService();

    void addTorrent(const std::string& path, const std::string& savePath);

    void update();

    void start();

    ~TorrentService();

    void resumeAll();

    void pauseAll();

    void pause( const size_t& tid,const size_t& fid );

    void resume ( const size_t& tid,const size_t& fid);

    void removeTorrent(const size_t& tid){
            session_.removeTorrent(tid);
            torrentHandle_.erase(torrentHandle_.begin()+tid);
    }

    std::vector<Torrent> torrentHandle() const;
};

