/*  SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#pragma once
#include <string>

enum TorrentStatus{
    TORRENT_RUN = 1,
    TORRENT_STOP = 2,
};


class TorrentFile{

    std::string name_;
    std::int64_t progress_;
    std::uint64_t size_;
    std::size_t id_;
    size_t status_;

public:

    TorrentFile();


    std::string name() const;
    void setName(const std::string &name);


    std::uint64_t size() const;
    void setSize(const std::uint64_t &size);

    std::int64_t progress() const;
    void setProgress(std::int64_t progress);

    std::size_t id() const;
    void setId(const std::size_t &id);

    size_t status() const;
    void setStatus(const size_t &status);
};
