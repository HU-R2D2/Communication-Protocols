#include "../include/UART.hpp"
#include "../include/UartTester.hpp"
#include <iostream>
int main(){
    std::cout << "Hello!" << std::endl;
    UART u(COM4);
    UartTester t(&u, false);
    t.sayHi();
}