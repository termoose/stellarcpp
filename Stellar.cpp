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

ReplyPaymentRequest Stellar::SendStellar(const std::string& secret, const std::string &from, const std::string &to, int64_t stellars)
{
    // Converts to microstellars
    SubmitPaymentRequest req(secret, from, to, stellars * 1000000);
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

