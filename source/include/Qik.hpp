////
//  ██████╗  ██████╗ ██████╗  ██████╗ ██████╗ ███████╗███████╗ ██████╗██╗   ██╗███████╗
//  ██╔══██╗██╔═══██╗██╔══██╗██╔═══██╗██╔══██╗██╔════╝██╔════╝██╔════╝██║   ██║██╔════╝
//  ██████╔╝██║   ██║██████╔╝██║   ██║██████╔╝█████╗  ███████╗██║     ██║   ██║█████╗
//  ██╔══██╗██║   ██║██╔══██╗██║   ██║██╔══██╗██╔══╝  ╚════██║██║     ██║   ██║██╔══╝
//  ██║  ██║╚██████╔╝██████╔╝╚██████╔╝██║  ██║███████╗███████║╚██████╗╚██████╔╝███████╗
//  ╚═╝  ╚═╝ ╚═════╝ ╚═════╝  ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝ ╚═════╝ ╚═════╝ ╚══════╝
//
//
// @file Qik.hpp
// @date Created: 13-05-16
// @version 1.0
//
// @author Job verhaar
//
// @section LICENSE
// License: newBSD
//
// Copyright © 2016, HU University of Applied Sciences Utrecht.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
// - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// - Neither the name of the HU University of Applied Sciences Utrecht nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
// BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
// GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
// OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
////

#ifndef _QIK_HPP
#define _QIK_HPP

#include "ApplicationProtocol.hpp"


#define QIK_GET_FIRMWARE_VERSION         0x81
#define QIK_GET_ERROR_BYTE               0x82
#define QIK_GET_CONFIGURATION_PARAMETER  0x83
#define QIK_SET_CONFIGURATION_PARAMETER  0x84
#define QIK_MOTOR_M0_FORWARD             0x88
#define QIK_MOTOR_M0_FORWARD_8_BIT       0x89
#define QIK_MOTOR_M0_REVERSE             0x8A
#define QIK_MOTOR_M0_REVERSE_8_BIT       0x8B
#define QIK_MOTOR_M1_FORWARD             0x8C
#define QIK_MOTOR_M1_FORWARD_8_BIT       0x8D
#define QIK_MOTOR_M1_REVERSE             0x8E
#define QIK_MOTOR_M1_REVERSE_8_BIT       0x8F
#define QIK_2S12V10_MOTOR_M0_BRAKE       0x86
#define QIK_2S12V10_MOTOR_M1_BRAKE       0x87
#define QIK_2S12V10_GET_MOTOR_M0_CURRENT 0x90
#define QIK_2S12V10_GET_MOTOR_M1_CURRENT 0x91
#define QIK_2S12V10_GET_MOTOR_M0_SPEED   0x92
#define QIK_2S12V10_GET_MOTOR_M1_SPEED   0x9
#define QIK_CONFIG_DEVICE_ID                        0
#define QIK_CONFIG_PWM_PARAMETER                    1
#define QIK_CONFIG_SHUT_DOWN_MOTORS_ON_ERROR        2
#define QIK_CONFIG_SERIAL_TIMEOUT                   3
#define QIK_CONFIG_MOTOR_M0_ACCELERATION            4
#define QIK_CONFIG_MOTOR_M1_ACCELERATION            5
#define QIK_CONFIG_MOTOR_M0_BRAKE_DURATION          6
#define QIK_CONFIG_MOTOR_M1_BRAKE_DURATION          7
#define QIK_CONFIG_MOTOR_M0_CURRENT_LIMIT_DIV_2     8
#define QIK_CONFIG_MOTOR_M1_CURRENT_LIMIT_DIV_2     9
#define QIK_CONFIG_MOTOR_M0_CURRENT_LIMIT_RESPONSE 10
#define QIK_CONFIG_MOTOR_M1_CURRENT_LIMIT_RESPONSE 11

class Qik: public ApplicationProtocol
{
public:
    //! @fn  Qik::Qik(TransportProtocol t)
    //!
    //! @brief  Constructor of the Qik Application protocol
    //!
    //! @param  t       The transportprotocol that is used to send data.
    Qik(TransportProtocol t);
    
    //! @fn  Qik::getFrimwareVersion();
    //!
    //! @brief  reads the frimwareversion from the Qik.
    //!
    //! @return uint8_t The frimware version that is readed.    
    uint8_t getFirmwareVersion();

    //! @fn  Qik::getErrors();
    //!
    //! @brief  reads the Errors from the Qik.
    //!
    //! @return uint8_t The Errorcode version that is readed. 
    uint8_t getErrors();

    //! @fn  Qik::getConfigurationParameter(byte parameter);
    //!
    //! @brief  reads the configurated parameter from the qik;
    //!
    //! @param  parameter the parameter in range 0-11 that needs to be readed;
    //! @return uint8_t The value of the parameter that is readed;
    uint8_t getConfigurationParameter(byte parameter);

    //! @fn Qik::setConfigurationParamater(byte parameter, byte value);
    //!
    //! @brief  set a parameter of the qik
    //! 
    //! @param parameter  the parameter in range 0-11 that needs to be changed
    uint8_t setConfigurationParameter(byte parameter, byte value);


    //! @fn Qik::setM0Speed(int speed)
    //!
    //! @brief set the speed of motor 0
    //!
    //! @param speed the speed value for motor 0 in range 0-255
    void setM0Speed(int speed);

    //! @fn Qik::setM0Speed(int speed)
    //!
    //! @brief set the speed of motor 0
    //!
    //! @param speed the speed value for motor 1 in range 0-255
    void setM1Speed(int speed);

    //! @fn Qik::setSpeeds(int m0Speed, int m1Speed)
    //!
    //! @brief set the speeds of motor 1 and 2
    //!
    //! @param m0Speed the speed value for motor 0 in range 0-255
    //! @param m0Speed the speed value for motor 1 in range 0-255
    void setSpeeds(int m0Speed, int m1Speed);
    
    //! @fn Qik::setM0Brake(uint8_t brake)
    //!
    //! @brief set the brake for motor 0
    //!
    //! @param brake the brake value for motor 0
    void setM0Brake(uint8_t brake);
    
    //! @fn Qik::setM0Brake(uint8_t brake)
    //!
    //! @brief set the brake for motor 0
    //!
    //! @param brake the brake value for motor 1
    void setM1Brake(uint8_t brake);

    //! @fn Qik::setM0Brake(uint8_t brake)
    //!
    //! @brief set the brakes for motor 0 and 1
    //!
    //! @param m0Brake the brake value for motor 0
    //! @param m1Brake the brake value for motor 1
    void setBrakes(uint8_t m0Brake, uint8_t m1Brake);

    //! @fn Qik::getM0Current()
    //!
    //! @brief get the current of motor 0
    //!
    //! @return uint8_t the current value of motor 0
    uint8_t getM0Current();

    //! @fn Qik::getM1Current()
    //!
    //! @brief get the current of motor 1
    //!
    //! @return uint8_t the current value of motor 1
    uint8_t getM1Current();

    //! @fn Qik::getM0CurrentMilliamps()
    //!
    //! @brief get the current of motor 0 in milliamps
    //!
    //! @return unsigned int the current value of motor 0 in milliamps
    unsigned int getM0CurrentMilliamps();
    
    //! @fn Qik::getM1CurrentMilliamps()
    //!
    //! @brief get the current of motor 1 in milliamps
    //!
    //! @return unsigned int the current value of motor 1 in milliamps
    unsigned int getM1CurrentMilliamps();

    //! @fn Qik::getM0Speed()
    //!
    //! @brief get the speed of motor 0
    //!
    //! @return uint8_t the speed value of motor 0 in range 0-255.
    uint8_t getM0Speed();

    //! @fn Qik::getM1Speed()
    //!
    //! @brief get the speed of motor 1
    //!
    //! @return uint8_t the speed value of motor 1 in range 0-255.
    uint8_t getM1Speed();
private:
    uint8_t cmd[5];
};
#endif