#ifndef _REST_PROTOCOL_HPP
#define _REST_PROTOCOL_HPP

//#include "ApplicationProtocol.hpp"
#include "TransportListener.hpp"

#include "RESTCallBack.h"
#include "RESTEngine.h"
#include <string>
#include <vector>

class RestApplicationProtocol : public TransportListener{

public:
    RestApplicationProtocol();
    //RestApplicationProtocol(TransportProtocol &t);

    void addCallbackFunction(std::string link, std::string method, RESTCallBack * callBackAddition);

    std::vector<RESTCallBack *> getCallBackFunctions();

    void data_received(uint8_t * data) override;

    void invokeApiCall(std::string link, std::string method, std::string message);

    void getJsonAPIDump(std::string fileName);

private:

    std::vector<RESTCallBack * > listOfCallBacks;
    RESTEngine engine;
};

#endif
