#include "gtest/gtest.h"
#include "../source/include/TCPSocket.hpp"


TEST(TCPSocketTransportProtocol, TestConnection){
  TCPSocket sock1("127.0.0.1", "27015");

  sock1.connect();
  Sleep(1000);
  std::cout<<"send wailawoe to server"<<std::endl;
  sock1.data_write((uint8_t *) "wailawoe", 8);
  Sleep(1000);
  sock1.data_write((uint8_t *) "halloiets", 9);
  Sleep(1000);

  sock1.disconnect();

}
