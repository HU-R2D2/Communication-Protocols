#include "../include/Qik.hpp"





Qik::Qik(TransportProtocol t): ApplicationProtocol(t){
    //maybe send start byte if autodetection is on
}

uint8_t Qik::getFirmwareVersion(){
    t.data_write(QIK_GET_FIRMWARE_VERSION);
    return t.data_read()[0];
}

uint8_t Qik::getErrors(){
    t.data_write(QIK_GET_ERROR_BYTE);
    return t.data_read()[0];
}

uint8_t Qik::getConfigurationParameter(byte parameter){
    cmd[0] = QIK_GET_CONFIGURATION_PARAMETER;
    cmd[1] = parameter;
    t.data_write(cmd,2);
    return t.data_read()[0];
}

uint8_t Qik::setConfigurationParameter(byte parameter, byte value){
    cmd[0] = QIK_SET_CONFIGURATION_PARAMETER;
    cmd[1] = parameter;
    cmd[2] = value;
    cmd[3] = 0x55;
    cmd[4] = 0x2A;
    t.data_write(cmd, 5);
    return t.data_read()[0];
}

void QiksetM0Speed(int speed){
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

void Qik::setM1Speed(int speed){
    boolean reverse = 0;
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
    t.data_write(cmd, 2);
}

void Qik::setSpeeds(int m0Speed, int m1Speed){
    setM0Speed(m0Speed);
    setM1Speed(m1Speed);
}

void Qik::setM0Brake(uint8_t brake){
    if (brake > 127)
    brake = 127;
    cmd[0] = QIK_2S12V10_MOTOR_M0_BRAKE;
    cmd[1] = brake;
    t.data_write(cmd, 2);
}

void Qik::setM1Brake(uint8_t brake){
    if (brake > 127)
    brake = 127;
    cmd[0] = QIK_2S12V10_MOTOR_M1_BRAKE;
    cmd[1] = brake;
    t.data_write(cmd, 2);
}

void Qik::setBrakes(uint8_t m0Brake, uint8_t m1Brake){
    setM0Brake(m0Brake);
    setM1Brake(m1Brake);
}

uint8_t getM0Current(){
    t.data_write(QIK_2S12V10_GET_MOTOR_M0_CURRENT);
    return t.data_read()[0];
}

uint8_t getM1Current(){
    t.data_write(QIK_2S12V10_GET_MOTOR_M1_CURRENT);
    return t.data_read()[0];
}
unsigned int getM0CurrentMilliamps(){
    return getM0Current() * 150;
}
unsigned int getM1CurrentMilliamps(){
    return getM1Current() * 150;
}

uint8_t getM0Speed(){
    t.data_write(QIK_2S12V10_GET_MOTOR_M0_SPEED);
    return t.data_read()[0];
}

uint8_t getM1Speed(){
    t.data_write(QIK_2S12V10_GET_MOTOR_M1_SPEED);
    return t.data_read()[0];
}