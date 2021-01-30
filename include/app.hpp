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

#include <iostream>
#include <memory>

#include <boost/filesystem.hpp>

#include <notimplementedexception.hpp>

#include <session.hpp>
#include <ioservice.hpp>
#include <respons.hpp>
#include <TorrentInfo.hpp>
#include <TorrentManager.hpp>


/*!
    \brief Application class.Essential for good style.
*/
class App{



    /*!
        \brief Signal to end the program
        \details Applications guarantees exit only after the cycle has run
    */
    void onExit_();
    /*!
        \brief Signal for adding a torrent
        \details Checks the name of the transferred file
    */

    void onAddMagnetTorrent_(const std::string &url, const std::string &savePath);

    /*!
        \brief Signal to delete torrent
        \details I guarantee verification id
    */
    void onRemoveTorrent_(const int64_t id);



    struct{
        bool run;
    }flags_;

public:


    App(int argc, char **argv);

    /*!
        \brief Launches the main loop of the application
    */
    int run();


private:

    void slotConnect_(){

        ioService_->onExit.connect(std::bind(&App::onExit_,this));
        ioService_->onAddMagnetTorrent.connect(std::bind(&App::onAddMagnetTorrent_,this,std::placeholders::_1,std::placeholders::_2));
        ioService_->onRemoveTorrent.connect(std::bind(&App::onRemoveTorrent_,this,std::placeholders::_1));


    }


    std::vector<std::string> arguments_;

    std::shared_ptr<Session>session_;
    std::unique_ptr<IoService>ioService_;
    std::unique_ptr<TorrentInfo>torrentInfo_;
    std::unique_ptr<TorrentManager>torrentManager_;

};






