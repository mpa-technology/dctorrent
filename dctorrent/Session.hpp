/*  SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#pragma once
#include "Torrent.hpp"
#include <libtorrent/session.hpp>


class Session{

    std::vector<Torrent>torrentList_;
    lt::session session_;
public:

    Torrent addTorrent(const std::string& path, const std::string &savePath);

    void removeTorrent(const size_t& id);


};
