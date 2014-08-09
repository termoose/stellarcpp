//
//  Stellar.cpp
//  stellar++
//
//  Created by Ole Andre Birkedal on 03/08/14.


#include "Stellar.h"


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

