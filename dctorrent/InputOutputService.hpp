#pragma once
#include <nlohmann/json.hpp>


class InputOutputService{

    std::string getString_();

    const std::array<std::string,6>commandList_{"info","exit","remove","pause","resume","add"};


    bool findCommand_(const std::string& command);

public:


    std::vector<std::string> getCommand();




};

