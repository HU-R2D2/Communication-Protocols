#ifndef _APPLICATION_HPP
#define _APPLICATION_HPP

#include "TransportProtocol.hpp"


/// An abstract class used to create a wrapper around a Applicaion Protocol.
/// \author Koen van der Kruk
/// \version 1.0
/// \date 8-6-2016
class ApplicationProtocol{

public:

    /// Constructor to initialize a apllication protocol containing a transport protocol.
    /// \param t The transportprotocol used to transfer the data between multiple nodes
    ApplicationProtocol();//TransportProtocol & t){transport = t;};

    /// Can be used to change the TransportProtocol after the object is already initiliazed
    /// \param t The TransportProtocol used to transfer data between nodes.
    //void setTransportProtocol(TransportProtocol & t){transport = t;};

protected:
    //TransportProtocol & transport;
};

#endif
