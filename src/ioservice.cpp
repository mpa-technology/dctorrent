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



#include <ioservice.hpp>


IoService::IoService(){

    boost::locale::generator gen;
    std::locale loc = gen("");
    std::locale::global(loc);
    std::cout.imbue(loc);
    std::cerr.imbue(loc);
}

void IoService::work(const std::vector<TorrentFile>& torrentFiles){

    std::flush(std::cout);

    std::string inputStr;

    std::getline(std::cin,inputStr);


    auto resp = nlohmann::json::parse(inputStr);
    const std::vector<std::string>argv = resp;

    if(argv.at(0)=="exit"){
        onExit();
        return;
    }

    if(argv.at(0)=="info"){


        nlohmann::json json{ {"code",RESPONSE_CODE::CODE_OK} };

        for(auto& it : torrentFiles){
            json["torrent"] += it.json();
        }




        std::cout << json << std::endl;

    }

}
