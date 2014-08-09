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
        
        if(!doc.IsObject()) return;
        
        id = GetInt("id", doc);
        status = GetString("status", doc);
        type = GetString("type", doc);
        error_message = GetString("error_message", doc);
    }
    
    int64_t id;
    std::string status;
    std::string type;
    std::string error_message;
    
protected:
    template<typename T>
    std::string GetString(const std::string& key, const T & node)
    {
        if(!node.HasMember(key.c_str())) return std::string();
        
        const auto & value = node[key.c_str()];
        
        if(value.IsString()) return value.GetString();
        return std::string();
    }
    
    template<typename T>
    int64_t GetInt(const std::string& key, const T & node)
    {
        if(!node.HasMember(key.c_str())) return -1;
        
        const auto & value = node[key.c_str()];
        
        if(value.IsInt64()) return value.GetInt64();
        return -1;
    }

    rapidjson::Document doc;
};

class ReplyPaymentRequest : public ReplyBase
{
public:
    ReplyPaymentRequest(const std::string& reply)
    : ReplyBase(reply)
    {
        if(!doc.IsObject()) return;
        if(!doc.HasMember("result")) return;
        const auto & result = doc["result"];
        
        message = GetString("engine_result_message", result);
        result_code = GetInt("engine_result_code", result);
    }
    
    std::string message;
    int64_t result_code;
};

class ReplyAccountInfo : public ReplyBase
{
public:
    ReplyAccountInfo(const std::string& reply)
    : ReplyBase(reply), balance(0)
    {
        if(!doc.IsObject()) return;
        if(!doc.HasMember("result")) return;
        const auto & result = doc["result"];
        
        if(!result.HasMember("account_data")) return;
        const auto & account_data = result["account_data"];
        balance = std::atoll(GetString("Balance", account_data).c_str());
    }
    
    int64_t balance;
};

#endif
