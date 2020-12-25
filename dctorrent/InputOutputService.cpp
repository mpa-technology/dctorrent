#include "InputOutputService.hpp"


std::string InputOutputService::getString_(){
    std::string input;
    std::getline(std::cin, input);
    return input;
}

bool InputOutputService::findCommand_(const std::string &command){
    for(const auto&it : commandList_){
        if(command.find(it)!=command.npos)
            return true;
    }

    return false;
}

std::vector<std::string> InputOutputService::getCommand(){
    std::vector<std::string>carg;



    nlohmann::json line;

    try {
        line = nlohmann::json::parse(getString_());
    } catch (std::exception const& exception) {
        std::cout <<  exception.what() << std::endl;
        return {"@NULL"};
    }





    if( !line.is_array() || line.empty() || !findCommand_(line.at(0)) )
        return {"@NULL"};


    for(const auto& it : line)
        carg.push_back(it);


    return carg;
}
