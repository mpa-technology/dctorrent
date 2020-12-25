/*  SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#pragma once

#include "TorrentFile.hpp"
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_info.hpp>
#include <libtorrent/torrent_status.hpp>
#include <vector>


class Torrent{


    lt::torrent_handle torrentHandle_;

    std::vector<TorrentFile>torrentFiles_;

    size_t id_;

    size_t status_;

public:

    Torrent(lt::torrent_handle torrentHandle);


    void update();

    std::string name (  )const;


    float progress (  )const;


    bool isFinished (  )const;

    void resumeAll();

    void pause(const size_t& fid);
    void resume(const size_t& fid);


    void pauseAll();

    std::vector<TorrentFile> getFiles()const;


    size_t id() const;

    size_t status() const;

    lt::torrent_handle getTorrentHandle() const;
};
