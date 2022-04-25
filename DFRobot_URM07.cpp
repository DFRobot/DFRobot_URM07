/*!
 * @file  DFRobot_URM07.cpp
 * @brief  The library of the ultrasonic sensor
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng@dfrobot.com)
 * @version     V1.0.0
 * @date        2022-03-14
 * @url         https://github.com/DFRobot/DFRobot_URM07
 */
#include "DFRobot_URM07.h"

static uint8_t checksum(uint8_t*CMD,uint8_t length)
{
  uint8_t sum=0;
  for (int i = 0; i < length;i++)
  {
    sum += CMD[i];
  }
  return sum;
}

void DFRobot_URM07::changeBaudreat(uint8_t baud_reat)
{
  writeCmd(SET_BAUD_REAT, &baud_reat,1);
}

void DFRobot_URM07::changeAddr(uint8_t addr)
{
  writeCmd(SET_ADDR, &addr, 1);
}

uint16_t DFRobot_URM07::gainDistance(void)
{
  uint8_t data_buf[7];
  uint16_t distance;
  receiveData(GET_DIS_CMD, data_buf, 8);
  if (data_buf[7] != checksum(data_buf,7))
    return 0;
  else
  {
    distance = ((data_buf[5] << 8) | data_buf[6]);
    if (distance == 0xffff)
      return 0;
    else
      return distance;
  }
}

float DFRobot_URM07::gainTemperature(void)
{
  uint8_t data_buf[7];
  uint16_t temperature;
  receiveData(GET_TEMP_CMD, data_buf, 8);
  if (data_buf[7] != checksum(data_buf, 7))
    return 0;
  else
  {
    temperature = ((data_buf[5] << 8) | data_buf[6]);
    if (temperature == 0xffff)
      return 0;
    else
      return temperature/10;
  }
}

#if (!defined ARDUINO_ESP32_DEV) && (!defined __SAMD21G18A__)
DFRobot_URM07_SoftwareSerial::DFRobot_URM07_SoftwareSerial(SoftwareSerial *softserial, uint32_t buadreat, uint8_t addr)
{
  _softserial = softserial;
  _softserial->begin(buadreat);
  _addr = addr;
}

void DFRobot_URM07_SoftwareSerial::writeCmd(uint8_t CMD, uint8_t *data_buf,uint8_t data_len)
{
  uint8_t cmd_buff[MAX_LEN];
  cmd_buff[0] = HEADER_H;
  cmd_buff[1] = HEADER_L;
  cmd_buff[2] = _addr;
  cmd_buff[3] = data_len;
  cmd_buff[4] = CMD;
  for (int i = 0; i < data_len;i++)
  {
    cmd_buff[5 + i] = data_buf[i];
  }
  cmd_buff[5 + data_len] = checksum(cmd_buff, 5 + data_len);
  for (int i = 0; i < 6 + data_len;i++)
  {
    _softserial->write(cmd_buff[i]);
  }
}

int DFRobot_URM07_SoftwareSerial::receiveData(uint8_t CMD, uint8_t *data_buf, uint8_t data_len)
{
  uint8_t cmd_buff[MAX_LEN];
  cmd_buff[0] = HEADER_H;
  cmd_buff[1] = HEADER_L;
  cmd_buff[2] = _addr;
  cmd_buff[3] = 0;
  cmd_buff[4] = CMD;
  cmd_buff[5] = checksum(cmd_buff, 5);
  for (int i = 0; i < 6;i++)
  {
    _softserial->write(cmd_buff[i]);
  }
  uint32_t time = millis();
  uint8_t length;
  while ((millis() - time) < 3000)
  {
    length = _softserial->available();
    if (length == data_len)
      break;
  }
  if(length != data_len)
  {
    return ERROR;
  }
  for (int i = 0; i < length; i++)
  {
    data_buf[i] = _softserial->read();
  }
  return SUCCESS;
}

#else
DFRobot_URM07_HardwareSerial::DFRobot_URM07_HardwareSerial(HardwareSerial *hardserial, uint32_t buadreat, uint8_t addr)
{
  _hardserial = _hardserial;
  _hardserial->begin(buadreat);
  _addr = addr;
}

void DFRobot_URM07_HardwareSerial::writeCmd(uint8_t CMD, uint8_t *data_buf, uint8_t data_len)
{
  uint8_t cmd_buff[MAX_LEN];
  cmd_buff[0] = HEADER_H;
  cmd_buff[1] = HEADER_L;
  cmd_buff[2] = _addr;
  cmd_buff[3] = data_len;
  cmd_buff[4] = CMD;
  for (int i = 0; i < data_len; i++)
  {
    cmd_buff[5 + i] = data_buf[i];
  }
  cmd_buff[5 + data_len] = checksum(cmd_buff, 5 + data_len);
  for (int i = 0; i < 6 + data_len; i++)
  {
    _hardserial->write(cmd_buff[i]);
  }
}
int DFRobot_URM07_HardwareSerial::receiveData(uint8_t CMD, uint8_t *data_buf, uint8_t data_len)
{
  uint8_t cmd_buff[MAX_LEN];
  cmd_buff[0] = HEADER_H;
  cmd_buff[1] = HEADER_L;
  cmd_buff[2] = _addr;
  cmd_buff[3] = 0;
  cmd_buff[4] = CMD;
  cmd_buff[5] = checksum(cmd_buff, 5);
  for (int i = 0; i < 6; i++)
  {
    _hardserial->write(cmd_buff[i]);
  }
  uint32_t time = millis();
  uint8_t length;
  while ((millis() - time) < 3000)
  {
    length = _hardserial->available();
    if (length == data_len)
      break;
  }
  if (length != data_len)
  {
    return ERROR;
  }
  for (int i = 0; i < length; i++)
  {
    data_buf[i] = _hardserial->read();
  }
  return SUCCESS;
}

#endif
