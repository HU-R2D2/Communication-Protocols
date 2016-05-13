#include "../include/UART.hpp"

UART::UART(int com, uint32_t baud, int bytesize, int paritytype, double stopbits, int flow) :
comport(com),
baudrate(baud),
databitcount(bytesize),
parity(paritytype),
stopbitcount(stopbits),
flowcontrol(flowcontrol)
{
	serial::stopbits_t stopbittype;
	if(stopbits == 1.5){
		stopbittype = serial::stopbits_t::stopbits_one_point_five;
	}
	else{
		stopbittype = stopbitcount;
	}

	serial::flowcontrol_t flowcontroltype;
	if(flowcontrol == 1){
		flowcontroltype = serial::flowcontrol_t::flowcontrol_software;
	}
	else if(flowcontrol = 2){
		flowcontroltype = serial::flowcontrol_t::flowcontrol_hardware;
	}
	else{
		flowcontroltype = 0;
	}
	serial::Serial("COM"+comport, (uint32_t) baudrate, serial::Timeout::simpleTimeout(serial::Timeout::max()), databitcount, parity, stopbittype, flowcontroltype);
}

void UART::data_write(uint8_t* data){
	
}

uint8_t* UART::data_read(){

}

void UART::connect(){

}

void UART::disconnect(){

}

void UART::flush(){

}

bool UART::is_open(){

}