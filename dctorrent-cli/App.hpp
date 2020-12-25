#pragma once
#include <iostream>
#include <boost/process.hpp>
#include <nlohmann/json.hpp>
#include <boost/algorithm/string.hpp>



class App{

    boost::process::ipstream pipe;
    boost::process::opstream pipeo;
    boost::process::child dtProcess;


    std::string getRespones_();

public:

    App();

    ~App();

    int run();


};

