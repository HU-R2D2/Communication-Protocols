#ifndef _TRANSPORT_LISTENER_HPP
#define _TRANSPORT_LISTENER_HPP

class TransportListener{

public:
   virtual void data_received(uint8_t * data) = 0;
};

#endif
