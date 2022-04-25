/*!
 * @file  DFRobot_URM07.h
 * @brief  The library of the ultrasonic sensor
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng@dfrobot.com)
 * @version     V1.0.0
 * @date        2022-03-14
 * @url         https://github.com/DFRobot/DFRobot_URM07
 */

#ifndef __DFRobot_GAS_H__
#define __DFRobot_GAS_H__
#include "Arduino.h"
#if (!defined ARDUINO_ESP32_DEV) && (!defined __SAMD21G18A__)
#include "SoftwareSerial.h"
#else
#include "HardwareSerial.h"
#endif

#define ERROR -1
#define SUCCESS 0

#define MAX_LEN 20

#define HEADER_H 0x55    
#define HEADER_L 0xAA    
#define GET_DIS_CMD 0x02
#define GET_TEMP_CMD 0x03
#define SET_BAUD_REAT 0x08
#define SET_ADDR 0x55

#define BAUD_REAT_1200BPS 0X00
#define BAUD_REAT_2400BPS 0X01
#define BAUD_REAT_4800BPS 0X02
#define BAUD_REAT_9600BPS 0X03
#define BAUD_REAT_14400BPS 0X04
#define BAUD_REAT_19200BPS 0X05
#define BAUD_REAT_28800BPS 0X06
#define BAUD_REAT_38400BPS 0X07
#define BAUD_REAT_57600BPS 0X08
#define BAUD_REAT_115200BPS 0X09
#define BAUD_REAT_128000BPS 0X0A
#define BAUD_REAT_256000BPS 0X0B

class DFRobot_URM07
{
  public:
    /**
     * @fn gainDistance
     * @brief Get the distance between the sensor and the object ahead
     * @return uint16_t the distance between the sensor and the object ahead
     */
    uint16_t gainDistance(void);

    /**
     * @fn gainTemperature
     * @brief Get sensor board temp
     * @return float board temp
     */
    float gainTemperature(void);

    /**
     * @fn changeBaudreat
     * @brief Change serial communication baud rate
     * @param baud_reat baud rate
     * @n     BAUD_REAT_1200BPS 
     * @n     BAUD_REAT_2400BPS 
     * @n     BAUD_REAT_4800BPS 
     * @n     BAUD_REAT_9600BPS 
     * @n     BAUD_REAT_14400BPS 
     * @n     BAUD_REAT_19200BPS 
     * @n     BAUD_REAT_28800BPS 
     * @n     BAUD_REAT_38400BPS 
     * @n     BAUD_REAT_57600BPS 
     * @n     BAUD_REAT_115200BPS
     * @n     BAUD_REAT_128000BPS
     * @n     BAUD_REAT_256000BPS
     */
    void changeBaudreat(uint8_t baud_reat);

    /**
     * @fn  changeAddr
     * @brief Change the default address of the sensor
     * @param addr the address to be changed
     */
    void changeAddr(uint8_t addr);
  private:
    virtual void writeCmd(uint8_t CMD, uint8_t *data_buf, uint8_t data_len) = 0;
    virtual int receiveData(uint8_t CMD, uint8_t *data_buf, uint8_t data_len) = 0;
};

#if (!defined ARDUINO_ESP32_DEV) && (!defined __SAMD21G18A__)
class DFRobot_URM07_SoftwareSerial : public DFRobot_URM07
{
  public:
    DFRobot_URM07_SoftwareSerial(SoftwareSerial *softserial, uint32_t buadreat, uint8_t addr);
  private:
    void writeCmd(uint8_t CMD, uint8_t *data_buf, uint8_t data_len);
    int receiveData(uint8_t CMD, uint8_t *data_buf, uint8_t data_len);
    SoftwareSerial *_softserial;
    uint32_t _buadreat;
    uint8_t _addr;
};
#else
class DFRobot_URM07_HardwareSerial : public DFRobot_URM07
{
  public:
    DFRobot_URM07_HardwareSerial(HardwareSerial *hardserial, uint32_t buadreat, uint8_t addr);
  private:
    void writeCmd(uint8_t CMD, uint8_t *data_buf, uint8_t data_len);
    int receiveData(uint8_t CMD, uint8_t *data_buf, uint8_t data_len);
    HardwareSerial* _hardserial;
    uint32_t _buadreat;
    uint8_t _addr;
};
#endif
#endif
