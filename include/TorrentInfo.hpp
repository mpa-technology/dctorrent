#pragma once
#include <memory>
#include <boost/json.hpp>
#include <session.hpp>

class TorrentInfoException : public std::exception{


public:

    TorrentInfoException(const std::string &msg):msg_(msg){}


   ~TorrentInfoException(){}

    const char *what() const noexcept
    {
        return msg_.c_str();
    }


private:
    const std::string msg_;


};

class TorrentInfo{
public:


    using sessionPointType = std::shared_ptr<Session>;
    using stringList = std::vector<std::string>;
    using jsonList = std::vector<boost::json::object>;

    TorrentInfo(sessionPointType session);

    static stringList getTorrentFileNames();

    static boost::json::object getTorrentInfo(const int64_t id);

    static jsonList getAllTorrentInfo();



private:
    static TorrentInfo* torrent_;
    sessionPointType session_;


    static void verify_();



};

