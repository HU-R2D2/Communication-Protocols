#ifndef _APPLICATION_HPP
#define _APPLICATION_HPP

#include "TransportProtocol.hpp"

class ApplicationProtocol{

public:
    ApplicationProtocol(TransportProtocol * t = nullptr){transport = t;};
    void setTransportProtocol(TransportProtocol * t){transport = t;};

protected:
    TransportProtocol * transport;
};

#endif
