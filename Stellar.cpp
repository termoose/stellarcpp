//
//  Stellar.cpp
//  stellar++
//
//  Created by Ole Andre Birkedal on 03/08/14.


#include "Stellar.h"

ReplyAccountInfo Stellar::GetInfo(const std::string &account)
{
    AccountInfoRequest req(account);
    const std::string & reply_json = request(req.json());
    
    ReplyAccountInfo reply(reply_json);
    
    return reply;
}

ReplyPaymentRequest Stellar::Pay(const std::string &from, const std::string &to, int64_t stellars)
{
    SubmitPaymentRequest req(from, to, stellars);
    const std::string & reply_json = request(req.json());
    
    ReplyPaymentRequest reply(reply_json);
    
    return reply;
}

std::string Stellar::request(const std::string& req, int timeout)
{
    std::string reply;
    
    std::async([&]
               {
                   std::lock_guard<std::mutex> lock(socket_mutex);
                   std::atomic_bool finished(false);
                   
                   ws->send(req);
                   
                   while(!finished)
                   {
                       
                       ws->dispatch([&](const std::string & r)
                                    {
                                        reply = r;
                                        finished = true;
                                    });
                       ws->poll(timeout);
                   }
               });
    
    return reply;
}

