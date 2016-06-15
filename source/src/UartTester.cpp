#include "../include/UartTester.hpp"
#include <iostream>

UartTester::UartTester(TransportProtocol *t, bool listen): ApplicationProtocol(t), listen(listen){
    transport->set_listener(this);
}

void UartTester::data_received(uint8_t * data){
    static int count = 0;
    ++count;
    if(listen){
        if(count == 2){
            backHi();
            count = 0;
        }
    }
    else{
        if(count == dataBytesNeeded){
            dataReady = true;
            count = 0;
        }
    }   
}

uint8_t* UartTester::sayHi(){
    //std::cout << "Sending: hi" << std::endl;
    transport->data_write((uint8_t *) "Hallo thijsHallo thijsHallo thijsHallo thijsHallo thijsHallo thijsHallo thijsHallo thijsHallo thijsHallo thijs", 110);
    //uint8_t* answer = getAnswer(2);
    //std::cout << "received: " << answer << std::endl;
}

void UartTester::backHi(){
    uint8_t hi[2];
    hi[1] = 'h';
    hi[2] = 'a';
    transport->data_write(hi, 2);
}

uint8_t* UartTester::getAnswer(int dataLength){
    dataBytesNeeded = 2;
    dataReady = false;
    return transport->data_read();
}