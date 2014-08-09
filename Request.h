//
//  Request.h
//  stellar++
//
//  Created by Ole Andre Birkedal on 05/08/14.


#ifndef stellar___Request_h
#define stellar___Request_h

#include "document.h"
#include "stringbuffer.h"
#include "writer.h"

enum RequestType { AccountInfo, AccountCurrencies, Submit, Subscribe };
static int64_t message_id = 0;

// Base class for all request types that can be sent to the Stellar API
class RequestBase
{
public:
    RequestBase(RequestType type) : type(type)
    {
        doc.SetObject();
        
        rapidjson::Value id(message_id);
        rapidjson::Value type_string(rapidjson::kStringType);
        
        switch (type)
        {
            case AccountInfo:
                type_string.SetString("account_info");
                break;
                
            case AccountCurrencies:
                type_string.SetString("account_currencies");
                break;
                
            case Subscribe:
                type_string.SetString("subscibe");
                break;
                
            case Submit:
                type_string.SetString("submit");
                break;
                
            default:
                break;
        }
        
        doc.AddMember("command", type_string, doc.GetAllocator());
        doc.AddMember("id", id, doc.GetAllocator());
        
        ++message_id;
    }
    
    // JSON request object -> std::string
    std::string json() const
    {
        rapidjson::StringBuffer string_buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(string_buffer);
        
        doc.Accept(writer);
        
        return string_buffer.GetString();
    }
    
protected:
    void AddString(const std::string& key, const std::string& value)
    {
        rapidjson::Value str_value(rapidjson::kStringType);
        rapidjson::Value str_key(rapidjson::kStringType);
        
        str_value.SetString(value.c_str(), doc.GetAllocator());
        str_key.SetString(key.c_str(), doc.GetAllocator());
        
        doc.AddMember(str_key, str_value, doc.GetAllocator());
    }
    
    RequestType type;
    rapidjson::Document doc;
};

// Separate classes for each kind of Stellar API request
class SubmitPaymentRequest : public RequestBase
{
public:
    SubmitPaymentRequest(const std::string& from, const std::string& to, unsigned int stellars)
    : RequestBase(Submit)
    {
        AddString("secret", from);
        
        rapidjson::Value tx_json(rapidjson::kObjectType);
        
        rapidjson::Value account(rapidjson::kStringType);
        account.SetString(to.c_str(), doc.GetAllocator());
        
        rapidjson::Value transaction_type(rapidjson::kStringType);
        transaction_type.SetString("Payment");
        
        rapidjson::Value value(stellars);
        
        tx_json.AddMember("TransactionType", transaction_type, doc.GetAllocator());
        tx_json.AddMember("Destination", account, doc.GetAllocator());
        tx_json.AddMember("Amount", value, doc.GetAllocator());
        
        doc.AddMember("tx_json", tx_json, doc.GetAllocator());
    }
};

class AccountInfoRequest : public RequestBase
{
public:
    AccountInfoRequest(const std::string& account)
    : RequestBase(AccountInfo)
    {
        AddString("account", account);
    }
};

class AccountCurrenciesRequest : public RequestBase
{
public:
    AccountCurrenciesRequest(const std::string& account)
    : RequestBase(AccountCurrencies)
    {
        AddString("account", account);
    }
};

#endif
