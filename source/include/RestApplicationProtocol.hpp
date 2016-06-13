#ifndef _REST_PROTOCOL_HPP
#define _REST_PROTOCOL_HPP

//#include "ApplicationProtocol.hpp"
#include "TransportListener.hpp"
#include <fstream>
#include <iostream>
#include "RESTCallBack.hpp"
#include "RESTEngine.hpp"
#include <string>
#include <vector>

/// An extension on ApplicationProtocol with support for REST api.
/// \author Koen van der Kruk
/// \version 1.0
/// \date 8-6-2016
class RestApplicationProtocol : public TransportListener{//, public ApplicationProtocol{

public:

    /// Second constructor with support for the TransportProtocol.
    RestApplicationProtocol(); //TransportProtocol & t

    /// Destructs the ApplicationProtocol object so the TransportProtocol is also removed.
    ~RestApplicationProtocol();

    /// This will assign a new function as callback function.
    /// \param link The http url to access
    /// \param method The http method, such as POST, PUT, DELETE, GET
    /// \param callBackAddition The function that receives the callback message.
    void addCallbackFunction(std::string link, std::string method, RESTCallBack * callBackAddition);

    //// RestApplicationProtocol is a TransportListener that will receive incoming messages.
    /// \param data The incoming data package
    void data_received(uint8_t * data) override;

    /// Invoke API call, callback to another function.
    /// \param link The url conencted to the callback function
    /// \param method The HTTP method that can be used to invoke an API call over HTTP.
    /// \param message The message for the callback function
    void invokeApiCall(std::string link, std::string method, std::string message);

    /// This function will dump a full REST api in json format.
    /// \param fileName The filename is used to dump the REST API in json format. The same directory is used as the current running program.
    void getJsonAPIDump(std::string fileName);

private:
    RESTEngine engine;
};

#endif
