/*  SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
    SPDX-FileCopyrightText: 2020 Maxim Palshin <palshin.maxim.alekseevich@gmail.com>
    SPDX-License-Identifier: BSD 3-Clause "New" or "Revised" License
*/



#pragma once
#include <vector>
#include <boost/algorithm/string.hpp>

#include "TorrentService.hpp"
#include "InputOutputService.hpp"
#include "Logger.hpp"

class App{

    std::vector<std::string>arguments_;
    std::string apppath_;
    TorrentService torrentService_;
    bool isRun_;
    InputOutputService inputOutputService_;

public:

    App(const int& argc,char** argv);

    void command (const std::vector<std::string>& command);

    int run();

};
