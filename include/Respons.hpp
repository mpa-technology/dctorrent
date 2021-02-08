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



#pragma once

#include <string>

/*! This enum contains a list of response codes */
enum class RESPONSE_CODE{


    START_FAILURE, /*!< dctorrent start error */
    START_OK, /*!< dctorrent start ok */
    EXIT_OK, /*!< dctorrent exit */
    CODE_OK, /*!< response code ok */
    CODE_ERROR, /*!< response code error */
    CODE_NON, /*!< response non code */
    CODE_CRITICAL_ERROR
};




constexpr RESPONSE_CODE toResponseCode ( const int code){



    switch (static_cast<RESPONSE_CODE>(code)) {
    case RESPONSE_CODE::START_FAILURE:return RESPONSE_CODE::START_FAILURE;
    case RESPONSE_CODE::START_OK:return RESPONSE_CODE::START_OK;
    case RESPONSE_CODE::EXIT_OK:return RESPONSE_CODE::EXIT_OK;
    case RESPONSE_CODE::CODE_OK:return RESPONSE_CODE::CODE_OK;
    case RESPONSE_CODE::CODE_ERROR:return RESPONSE_CODE::CODE_ERROR;
    case RESPONSE_CODE::CODE_NON:return RESPONSE_CODE::CODE_NON;
    case RESPONSE_CODE::CODE_CRITICAL_ERROR:return RESPONSE_CODE::CODE_CRITICAL_ERROR;
    }

    return RESPONSE_CODE::CODE_NON;
}


class Response{

public:


    Response();

    void setResponseCode(const int responseCode);


    void setResponseCode(const RESPONSE_CODE responseCode);


    RESPONSE_CODE getResponseCode()const;



    std::string getMessage() const;
    void setMessage(const std::string &message);

    bool operator==(const Response &response)const;


    bool operator!=(const Response &response)const;

    bool empty()const;

private:

    RESPONSE_CODE responseCode_;
    std::string message_;

};
