#include "../include/Qik.hpp"





Qik::Qik(TransportProtocol t): ApplicationProtocol(t){
    //maybe send start byte if autodetection is on
}

uint8_t Qik::get_firmware_version(){
    t.data_write(QIK_GET_FIRMWARE_VERSION);
    return t.data_read()[0];
}

uint8_t Qik::get_errors(){
    t.data_write(QIK_GET_ERROR_BYTE);
    return t.data_read()[0];
}

uint8_t Qik::get_configuration_parameter(byte parameter){
    cmd[0] = QIK_GET_CONFIGURATION_PARAMETER;
    cmd[1] = parameter;
    t.data_write(cmd,2);
    return t.data_read()[0];
}

uint8_t Qik::set_configuration_parameter(byte parameter, byte value){
    cmd[0] = QIK_SET_CONFIGURATION_PARAMETER;
    cmd[1] = parameter;
    cmd[2] = value;
    cmd[3] = 0x55;
    cmd[4] = 0x2A;
    t.data_write(cmd, 5);
    return t.data_read()[0];
}

void Qik::set_m0_speed(int speed){
    boolean reverse = 0;
    if (speed < 0){
        speed = -speed; // make speed a positive quantity
        reverse = 1; // preserve the direction
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
    t.data_write(cmd, 2);
}

void Qik::set_m1_speed(int speed){
    boolean reverse = 0;
    if (speed < 0){
        speed = -speed; // make speed a positive quantity
        reverse = 1; // preserve the direction
    }
    if (speed > 255)
    speed = 255b;
    if (speed > 127){
    // 8-bit mode: actual speed is (speed + 128)
    cmd[0] = reverse ? QIK_MOTOR_M1_REVERSE_8_BIT : QIK_MOTOR_M1_FORWARD_8_BIT;
    cmd[1] = speed - 128;
    }
    else{
    cmd[0] = reverse ? QIK_MOTOR_M1_REVERSE : QIK_MOTOR_M1_FORWARD;
    cmd[1] = speed;
    }
    t.data_write(cmd, 2);
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
    t.data_write(cmd, 2);
}

void Qik::set_m1_brake(uint8_t brake){
    if (brake > 127)
    brake = 127;
    cmd[0] = QIK_2S12V10_MOTOR_M1_BRAKE;
    cmd[1] = brake;
    t.data_write(cmd, 2);
}

void Qik::set_brakes(uint8_t m0Brake, uint8_t m1Brake){
    set_m0_brake(m0Brake);
    set_m1_brake(m1Brake);
}

uint8_t get_m0_current(){
    t.data_write(QIK_2S12V10_GET_MOTOR_M0_CURRENT);
    return t.data_read()[0];
}

uint8_t get_m1_current(){
    t.data_write(QIK_2S12V10_GET_MOTOR_M1_CURRENT);
    return t.data_read()[0];
}
unsigned int get_m0_currentMilliamps(){
    return get_m0_current() * 150;
}
unsigned int get_m1_currentMilliamps(){
    return get_m1_current() * 150;
}

uint8_t get_m0_speed(){
    t.data_write(QIK_2S12V10_GET_MOTOR_M0_SPEED);
    return t.data_read()[0];
}

uint8_t get_m1_speed(){
    t.data_write(QIK_2S12V10_GET_MOTOR_M1_SPEED);
    return t.data_read()[0];
}