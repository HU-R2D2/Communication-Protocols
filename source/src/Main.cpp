#include "../include/UART.hpp"
#include "../include/UartTester.hpp"
#include <iostream>
#include <Windows.h>

int main(){
    std::cout << "Hello!" << std::endl;
    UART u(COM3);
    u.connect();
    UartTester t(&u, false);
    t.sayHi();
    while(true){
        t.sayHi();
        Sleep(100);
    }
}