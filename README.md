#Stellar C++ API

Very simple library that connects to the WebSocket Stellar API using [easywsclient](https://github.com/dhbaird/easywsclient) and [rapidjson](https://github.com/miloyip/rapidjson).

###Features:
1. Get account information
2. Send Stellars

###Todo:
1. Finish the subscriber mode
2. Support more of the Stellar API
3. Add exception handling to the JSON parsing
4. Support for several currencies


##Example
```C++
// Create Stellar object, connects to the Stellar network
Stellar stellar;

auto info = stellar.GetInfo("address");
std::cout << "Account balance: " << info.balance << std::endl;

// Send 1000 Stellar to yours truly
auto reply = stellar.SendStellar("secret", "your_address", "g9j5EDysguoofGCsDS357HeHAeCg2NbxaW", 1000);
std::cout << "Payment status: " << reply.status << std::endl;

```