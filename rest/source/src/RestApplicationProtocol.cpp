#include "../include/RestApplicationProtocol.hpp"



RestApplicationProtocol::RestApplicationProtocol():
ApplicationProtocol{}
{
    engine = RESTEngine();

}

RestApplicationProtocol::RestApplicationProtocol(TransportProtocol * t):
ApplicationProtocol{t}
{
    engine = RESTEngine();
    if(transport != nullptr){
      transport->t_connect();
    }
}

RestApplicationProtocol::~RestApplicationProtocol(){
  if(transport != nullptr){
    transport->t_disconnect();
    delete transport;
  }
}


void RestApplicationProtocol::addCallbackFunction(std::string link, std::string method, RESTCallBack * callBackAddition){
    engine.addCallBack(link,method,callBackAddition);
}

void RestApplicationProtocol::data_received(uint8_t * data){

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
