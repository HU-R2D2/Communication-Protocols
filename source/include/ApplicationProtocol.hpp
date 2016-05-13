#ifndef _APPLICATION_HPP
#define _APPLICATION_HPP

#include "TransportProtocol.hpp"

class ApplicationProtocol{

public:
    ApplicationProtocol();
    ApplicationProtocol(TransportProtocol &t);

private:
    TransportProtocol &transport;
};

#endif