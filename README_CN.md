# DFRobot_URM07
- [English Version](./README.md)

超声波测距是通过发射超声波，并计算传感器收到回声的时间差，从而得出传感器到目标物体距离的一种方法。 URM07是一款超低功耗的超声波测距模块，有效测量距离7.5米，支持3.0~5.5V宽电压供电，可直接兼容3.3V或者5V控制设备，例如Arduino，树莓派等。URM07平均工作电流仅5mA，待机电流仅14uA，绝大部分控制器IO端口便可以为单个或多个URM07模块提供工作电流。 从超声波测距的原理来看，距离的准确性会受到空气的温度和风向干扰，URM07内置温度传感器，可以读取周边环境温度，并自动补偿数据。传感器采用收发一体的超声波探头，探测夹角约为60°，外形小巧，质量轻盈。预留2.54间距-4P接口，采用UART通信方式，能够适应更多系统架构的二次开发与应用。 URM07-UART超声波传感器各项参数都经过我们长时间严格的实验测定和优化，具有一流的测距响应速度、稳定性、灵敏度及低功耗。

![正反面svg效果图](./resources/images/SEN0153.png)

## 产品链接(https://www.dfrobot.com.cn/goods-1391.html)

SKU:SEN0153

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性y)
* [历史](#历史)
* [创作者](#创作者)

## 概述

兼容Arduino所有平台的一个超声波传感器

## 库安装

使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。

## 方法

```C++
    /**
     * @fn gainDistance
     * @brief 获取前方障碍物到传感器的距离
     * @return uint16_t 障碍物距离
     */
    uint16_t gainDistance(void);

    /**
     * @fn gainTemperature
     * @brief 获取传感器板子的温度
     * @return float 板子温度
     */
    float gainTemperature(void);

    /**
     * @fn changeBaudreat
     * @brief 改变串口通信波特率
     * @param baud_reat 波特率
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
     * @brief 改变传感器默认地址
     * @param addr 想要修改的地址
     */
    void changeAddr(uint8_t addr);

```
## 兼容性

主板               | 通过  | 未通过   | 未测试   | 备注
------------------ | :----------: | :----------: | :---------: | -----
FireBeetle-ESP32  |      √       |             |            | 
FireBeetle-ESP8266|      √       |              |             | 
Mega2560  |      √       |             |            | 
Arduino uno |       √      |             |            | 
Leonardo  |      √       |              |             | 
Micro：bit  |      √       |              |             | 
M0  |      √       |              |             | 

## 历史

- 2022/3/14 - 1.0.0 版本

## 创作者

Written by PengKaixing(kaixing.peng@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))