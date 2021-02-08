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
#pragma once

#include <string>
#include <stdexcept>

#ifndef TORRENT_NO_DEPRECATE
#define TORRENT_NO_DEPRECATE
#endif

#include <libtorrent/units.hpp>
#include <libtorrent/download_priority.hpp>

enum class TORRENT_PRIORITY : int{

    DONT_DOWNLOAD = 0,
    DEFAULT_PRIORITY = 4,
    LOW_PRIORITY = 1,
    TOP_PRIORITY = 7,


};

TORRENT_PRIORITY toTorrentPriority(lt::download_priority_t value);

TORRENT_PRIORITY toTorrentPriority(const int value);


struct TorrentNode{
    int id;
    std::string name;
    std::int64_t size;
    std::int64_t progress;
    lt::file_index_t index;





    TORRENT_PRIORITY priority;


};


