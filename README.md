#Stellar C++ API

Connects to the WebSocket Stellar API using [easywsclient](https://github.com/dhbaird/easywsclient) and [rapidjson](https://github.com/miloyip/rapidjson).

###Features:
1. 


```C++
// Create Stellar object, connects to the Stellar network
Stellar stellar;

// Create the request
AccountInfoRequest req("g9j5EDysguoofGCsDS357HeHAeCg2NbxaW");

// Send json request to Stellar network
std::string reply = stellar.request(req.json());

std::cout << "Account information: " << reply << std::endl;

```