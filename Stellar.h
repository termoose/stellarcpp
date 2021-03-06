//
//  stellar.h
//  stellar++
//
//  Created by Ole Andre Birkedal on 03/08/14.


#ifndef stellar___stellar_h
#define stellar___stellar_h

#include <string>
#include <iostream>
#include <future>
#include <deque>
#include <mutex>

#include "easywsclient.hpp"

#include "Request.h"
#include "Reply.h"


using easywsclient::WebSocket;

class Stellar
{
public:
    Stellar() :
    ws(WebSocket::from_url("ws://live.stellar.org:9001"))
    {}
    
    ~Stellar()
    {}
    
    ReplyAccountInfo GetInfo(const std::string& account);
    ReplyPaymentRequest SendStellar(const std::string& secret, const std::string& from, const std::string& to, int64_t stellars);

private:
    std::string request(const std::string& req, int timeout = 0);
    void subscribe(const std::string& user);
    
    WebSocket::pointer ws;
    uint64_t m_id;
    std::mutex socket_mutex;
    
    std::deque<std::string> events;
};

#endif
