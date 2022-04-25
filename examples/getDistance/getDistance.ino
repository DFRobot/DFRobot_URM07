/*!
 * @file getDistance.ino
 * @brief Get sensor temp and the distance between the sensor and the object ahead
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author      PengKaixing(kaixing.peng@dfrobot.com)
 * @version  V1.0.0
 * @date  2022-03-14
 * @url https://github.com/DFRobot/DFRobot_URM07
 */
 
#include "DFRobot_URM07.h"

#if (!defined ARDUINO_ESP32_DEV) && (!defined __SAMD21G18A__)
/**
 * UNO:pin_3-----RX
 *     pin_4-----TX
 */
SoftwareSerial softserial(3,4);
DFRobot_URM07_SoftwareSerial URM07(&softserial,19200,0x11);
#else
/**
 * ESP32:IO16-----RX
 *       IO17-----TX
 */
  DFRobot_URM07_HardwareSerial URM07(&Serial2,19200,0x11); //ESP32HardwareSerial
#endif


void setup() 
{  
  Serial.begin(115200);
//  URM07.changeBaudreat(BAUD_REAT_19200BPS);
//  URM07.changeAddr(0x11);
}

void loop() 
{
  uint16_t distance = URM07.gainDistance();
  Serial.print("target distance is ");
  Serial.print(distance);
  Serial.println(" cm");
  float temperature = URM07.gainTemperature();
  Serial.print("target temperature is ");
  Serial.print(temperature);
  Serial.println(" ℃");
  delay(1000);
}
