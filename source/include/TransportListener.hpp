#ifndef _TRANSPORT_LISTENER_HPP
#define _TRANSPORT_LISTENER_HPP

#include <cstdint>

/// A listener interface to comminucatie to application protocols
/// \author Koen van der Kruk, Job Verhaar
/// \version 1.0
/// \date 8-6-2016
class TransportListener{

public:

   /// This function is called from the TransportProtocol to send data between multiple nodes.
   /// \param data The transfered data to the listener.
   virtual void data_received(uint8_t * data) = 0;
};

#endif
