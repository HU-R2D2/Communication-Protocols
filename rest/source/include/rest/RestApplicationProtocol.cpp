#include "RestApplicationProtocol.hpp"



RestApplicationProtocol::RestApplicationProtocol()//:
//ApplicationProtocol()
{
    engine = RESTEngine();
}

/*RestApplicationProtocol::RestApplicationProtocol(TransportProtocol &t){
    engine = RESTEngine();
}
*/
void RestApplicationProtocol::addCallbackFunction(std::string link, std::string method, RESTCallBack * callBackAddition){
    engine.addCallBack(link,method,callBackAddition);
    //listOfCallBacks.add(callBackAddition);
}

std::vector<RESTCallBack *> RestApplicationProtocol::getCallBackFunctions(){
    return listOfCallBacks;
}

void RestApplicationProtocol::data_received(uint8_t * data){

}

void RestApplicationProtocol::invokeApiCall(std::string link, std::string method, std::string message ){
    Dumais::JSON::JSON j1;
    engine.invoke(j1, link, method, message);

}

void RestApplicationProtocol::getJsonAPIDump(std::string fileName){

  #define CHECK(X) if (!(X)) { \
    std::cerr << "Failed to check " << #X << " at line " << __LINE__ << std::endl; \
    return EXIT_FAILURE; }


    Dumais::JSON::JSON json;
    engine.documentInterface(json);
    CHECK(!json.stringify(true).empty());

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
