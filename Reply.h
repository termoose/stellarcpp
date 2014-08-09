//
//  Reply.h
//  stellarcpp
//
//  Created by Ole Andre Birkedal on 09/08/14.

#ifndef stellarcpp_Reply_h
#define stellarcpp_Reply_h

#include "document.h"

class ReplyBase
{
public:
    ReplyBase(const std::string& reply)
    {
        doc.Parse<0>(reply.c_str());
        
        id = GetInt("id");
        status = GetString("status");
        type = GetString("type");
    }
    
protected:
    std::string GetString(const std::string& key)
    {
        if(!doc.HasMember(key.c_str())) return std::string();
        
        auto & value = doc[key.c_str()];
        
        if(value.IsString()) return value.GetString();
        return std::string();
    }
    
    int64_t GetInt(const std::string& key)
    {
        if(!doc.HasMember(key.c_str())) return -1;
        
        auto & value = doc[key.c_str()];
        
        if(value.IsInt()) return value.GetInt64();
        return -1;
    }
    
    int64_t id;
    std::string status;
    std::string type;
    
    rapidjson::Document doc;
};

#endif
