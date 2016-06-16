#include "../include/Qik.hpp"

Qik::Qik(TransportProtocol &t): ApplicationProtocol(t){
    //Add listener and connect uart
    transport.set_listener(this);
    transport.connect();
}

void Qik::data_received(uint8_t * data, int number_of_bytes){
    //Use count to wait till lenght of data is equal to the databytes needed.
    static int count = 0;
    ++count;
    if(count == dataBytesNeeded){
        dataReady = true;
        count = 0;
    }
}

uint8_t* Qik::get_answer(int dataLength){
    dataBytesNeeded = dataLength;
    dataReady = false;
    //Wait till dataReady is set true in function get_answer
    while(!dataReady){
    }
    return transport.data_read();
}


uint8_t Qik::get_firmware_version(){
    cmd[0] = QIK_GET_FIRMWARE_VERSION;
    transport.data_write(cmd,1);
    return get_answer(1)[0];
}

uint8_t Qik::get_errors(){
    cmd[0] = QIK_GET_ERROR_BYTE;
    transport.data_write(cmd,1);
    return get_answer(1)[0];
}

uint8_t Qik::get_configuration_parameter(uint8_t parameter){
    cmd[0] = QIK_GET_CONFIGURATION_PARAMETER;
    cmd[1] = parameter;
    transport.data_write(cmd,2);
    return get_answer(1)[0];
}

uint8_t Qik::set_configuration_parameter(uint8_t parameter, uint8_t value){
    cmd[0] = QIK_SET_CONFIGURATION_PARAMETER;
    cmd[1] = parameter;
    cmd[2] = value;
    cmd[3] = 0x55;
    cmd[4] = 0x2A;
    transport.data_write(cmd, 5);
    return get_answer(1)[0];
}

void Qik::set_m0_speed(int speed){
    bool reverse = false;
    if (speed < 0){
        speed = -speed;
        reverse = 1;
    }

    if (speed > 255)
    speed = 255;
    if (speed > 127){
    // 8-bit mode: actual speed is (speed + 128)
    cmd[0] = reverse ? QIK_MOTOR_M0_REVERSE_8_BIT : QIK_MOTOR_M0_FORWARD_8_BIT;
    cmd[1] = speed - 128;
    }
    else
    {
    cmd[0] = reverse ? QIK_MOTOR_M0_REVERSE : QIK_MOTOR_M0_FORWARD;
    cmd[1] = speed;
    }
    transport.data_write(cmd, 2);
}

void Qik::set_m1_speed(int speed){
    bool reverse = false;
    if (speed < 0){
        speed = -speed; // make speed a positive quantity
        reverse = 1; // preserve the direction
    }
    if (speed > 255)
    speed = 255;
    if (speed > 127){
    // 8-bit mode: actual speed is (speed + 128)
    cmd[0] = reverse ? QIK_MOTOR_M1_REVERSE_8_BIT : QIK_MOTOR_M1_FORWARD_8_BIT;
    cmd[1] = speed - 128;
    }
    else{
    cmd[0] = reverse ? QIK_MOTOR_M1_REVERSE : QIK_MOTOR_M1_FORWARD;
    cmd[1] = speed;
    }
    transport.data_write(cmd, 2);
}

void Qik::set_speeds(int m0Speed, int m1Speed){
    set_m0_speed(m0Speed);
    set_m1_speed(m1Speed);
}

void Qik::set_m0_brake(uint8_t brake){
    if (brake > 127)
    brake = 127;
    cmd[0] = QIK_2S12V10_MOTOR_M0_BRAKE;
    cmd[1] = brake;
    transport.data_write(cmd, 2);
}

void Qik::set_m1_brake(uint8_t brake){
    if (brake > 127)
    brake = 127;
    cmd[0] = QIK_2S12V10_MOTOR_M1_BRAKE;
    cmd[1] = brake;
    transport.data_write(cmd, 2);
}

void Qik::set_brakes(uint8_t m0Brake, uint8_t m1Brake){
    set_m0_brake(m0Brake);
    set_m1_brake(m1Brake);
}

uint8_t Qik::get_m0_current(){
    cmd[0] = QIK_2S12V10_GET_MOTOR_M0_CURRENT;
    transport.data_write(cmd, 1);
    return get_answer(1)[0];
}

uint8_t Qik::get_m1_current(){
    cmd[0] = QIK_2S12V10_GET_MOTOR_M1_CURRENT;
    transport.data_write(cmd, 1);
    return get_answer(1)[0];
}
unsigned int Qik::get_m0_current_milliamps(){
    return get_m0_current() * 150;
}
unsigned int Qik::get_m1_current_milliamps(){
    return get_m1_current() * 150;
}

uint8_t Qik::get_m0_speed(){
    cmd[0] = QIK_2S12V10_GET_MOTOR_M0_SPEED;
    transport.data_write(cmd, 1);
    return get_answer(1)[0];
}

uint8_t Qik::get_m1_speed(){
    cmd[0] = QIK_2S12V10_GET_MOTOR_M1_SPEED;
    transport.data_write(cmd, 1);
    return get_answer(1)[0];
}
