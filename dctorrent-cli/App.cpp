#include "App.hpp"


//TODO: MOVE
bool isRun(const nlohmann::json& json){

    return json.at(1).at(1) == "run";
}

std::string addTorrent(const std::string& line){

    std::vector<std::string>lv;
    boost::algorithm::split(lv,line,boost::is_any_of(" "));

    std::stringstream buf;
    buf << R"(["add",")"<<lv.at(1)<<R"("])";


    return buf.str();
}
//=============

std::string App::getRespones_(){
    std::string line;
    std::vector<std::string>list;


    while  ( dtProcess.running() &&  pipe && std::getline(pipe,line) && !line.empty() ){
        return  line;
    }




    return {"@NULL"};
}

App::App(){


    dtProcess = boost::process::child("dctorrent",boost::process::std_out > pipe,boost::process::std_in < pipeo);



    if(!dtProcess.running())
        throw std::runtime_error("error run process");


    try {
        if(!isRun(nlohmann::json::parse(getRespones_())))
            throw std::runtime_error("error run dctorrent");
    } catch (const std::exception& exp) {
        std::cerr << exp.what() << std::endl;
    }







}

App::~App(){

    if(dtProcess.running())
        dtProcess.terminate();

}

int App::run(){

    while (true) {



        std::string line;
        std::getline(std::cin,line);

        if(line == "info"){
            pipeo << R"(["info"])" << std::endl;
            std::cout << getRespones_() << std::endl;
        }

        if(line == "exit"){
            pipeo << R"(["exot"])" << std::endl;
            break;
        }



        if(line.find("add")!=line.npos){
            pipeo <<  addTorrent(line) << std::endl;
        }

    }




    return  EXIT_SUCCESS;
}
