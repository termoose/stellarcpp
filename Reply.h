//
//  Reply.h
//  stellarcpp
//
//  Created by Ole Andre Birkedal on 09/08/14.
//  Copyright (c) 2014 Ole Andre Birkedal. All rights reserved.
//

#ifndef stellarcpp_Reply_h
#define stellarcpp_Reply_h

#include "document.h"

class ReplyBase
{
    ReplyBase(const std::string& reply)
    {
        
    }
    
protected:
    int64_t id;
    std::string status;
    std::string type;
    
    rapidjson::Document doc;
};

#endif
