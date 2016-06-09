#include "../include/RestApplicationProtocol.hpp"


RestApplicationProtocol::RestApplicationProtocol()//: TransportProtocol & t
//ApplicationProtocol{t}
{
    engine = RESTEngine();
  //  transport.t_connect();

}

RestApplicationProtocol::~RestApplicationProtocol(){
  //  transport.t_disconnect();
//  engine.
}


void RestApplicationProtocol::addCallbackFunction(std::string link, std::string method, RESTCallBack * callBackAddition){
    engine.addCallBack(link,method,callBackAddition);
}

void RestApplicationProtocol::data_received(uint8_t * data){
//TODO cut string and method and message from http request? Use API or external library.
/*  std::string link = ""
  if(data[0] == "link"){
    link = data[1]
  }

    this.invokeApiCall(link,method,data);
    */
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
