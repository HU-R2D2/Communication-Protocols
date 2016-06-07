#ifndef _REST_PROTOCOL_HPP
#define _REST_PROTOCOL_HPP

#include "ApplicationProtocol.hpp"
#include "TransportListener.hpp"
#include <fstream>
#include <iostream>
#include "RESTCallBack.h"
#include "RESTEngine.h"
#include <string>
#include <vector>

class RestApplicationProtocol : public TransportListener, public ApplicationProtocol{

public:
    RestApplicationProtocol();
    ~RestApplicationProtocol();
    RestApplicationProtocol(TransportProtocol *t);

    void addCallbackFunction(std::string link, std::string method, RESTCallBack * callBackAddition);

    void data_received(uint8_t * data) override;

    void invokeApiCall(std::string link, std::string method, std::string message);

    void getJsonAPIDump(std::string fileName);

private:
    RESTEngine engine;
};

#endif
