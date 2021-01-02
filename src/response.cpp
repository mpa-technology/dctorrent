#include "../include/response.hpp"



std::int64_t Response::code() const
{
    return code_;
}

void Response::setCode(const std::int64_t &code)
{
    code_ = code;
}

std::string Response::message() const
{
    return message_;
}

void Response::setMessage(const std::string &message)
{
    message_ = message;
}

Response::Response()
{

}

std::string Response::toString()const{

    throw NotImplementedException;

}
