#pragma once

#include <notimplementedexception.hpp>


class Response{


    std::int64_t code_;
    std::string message_;
public:

    Response();



    std::string toString() const;


    std::int64_t code() const;
    void setCode(const std::int64_t &code);

    std::string message() const;
    void setMessage(const std::string &message);
};
