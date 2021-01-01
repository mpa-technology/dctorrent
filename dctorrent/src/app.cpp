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


#include "app.hpp"



App::App(int argc, char **argv){

    appPath_ = argv[0];

    for(int i = 1 ; i != argc; ++i)
        arguments_.push_back(argv[i]);

}

int App::run(){


    if(arguments_.empty()){
        std::cerr << "argc == 1 " << std::endl;
        return EXIT_SUCCESS;
    }


    session_ = std::make_unique<Session>();

    TorrentInfo torrentInfo(arguments_.at(0));
    torrentInfo.setSavePath( arguments_.size() >= 2 ? arguments_.at(1) : "." );

    auto torrent = session_->addTorrent(std::move(torrentInfo));


    std::string inputStr;


    while (true) {



        std::cin >> inputStr;

        if(inputStr == "exit")
            break;

        if(inputStr == "info"){


            std::cout << torrent.name() << '\t' << torrent.isFinished() << std::endl;

            for( const auto& it : torrent.getNode()){

                const auto progress = std::ceil( 100.0/static_cast<float>(it.size)*static_cast<float>(it.progress));
                std::string priority = !it.priority ? "[pause]" : "";


                std::cout << it.id <<  ") " << priority << it.name  <<  '\t' << progress << '%' << std::endl;
            }


        }


    }

    return EXIT_SUCCESS;
}
