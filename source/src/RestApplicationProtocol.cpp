#include "../include/RestApplicationProtocol.hpp"
#include <iostream>
#include <sstream>
#include <string>

RestApplicationProtocol::RestApplicationProtocol(TransportProtocol & t):
ApplicationProtocol{t}
{
    engine = RESTEngine();
    transport.connect();
}

RestApplicationProtocol::~RestApplicationProtocol(){
    transport.disconnect();
//  engine.
}


void RestApplicationProtocol::addCallbackFunction(std::string link, std::string method, RESTCallBack * callBackAddition){
    engine.addCallBack(link,method,callBackAddition);
}

void RestApplicationProtocol::data_received(uint8_t * data){
//TODO cut string and method and message from http request? Use API or external library.
//Send data like this: URL,METHOD,DATA
    std::stringstream ss(std::string(data));
    std::vector<std::string> result;

    while( ss.good() )
    {
        std::string substr;
        getline( ss, substr, ',' );
        result.push_back( substr );
    }
    std::string link = result.get(0);
    std::string method = result.get(1);
    std::string data = result.get(2);

    if(!link.empty() && !method.empty() && !data.empty())
    {
        this.invokeApiCall(link,method,data);
    } else{
      std::cout << "Wrong input, ignoring result" << "\n";
    }
}

void RestApplicationProtocol::invokeApiCall(std::string link, std::string method, std::string message ){
    Dumais::JSON::JSON j1;
    engine.invoke(j1, link, method, message);

}

void RestApplicationProtocol::getJsonAPIDump(std::string fileName){

    Dumais::JSON::JSON json;
    engine.documentInterface(json);

    Dumais::JSON::JSON swaggerSchema;
    engine.documentSwaggerInterface(swaggerSchema, "1", "title", "description", "http", "localhost", "/api");
    if (!swaggerSchema.isValid()) {
        std::cerr << "invalid JSON swagger schema" << std::endl;
    } else {
        std::ofstream swaggerSchemaFile(fileName);
        swaggerSchemaFile << swaggerSchema.stringify(true);
        swaggerSchemaFile.close();
    }

}
