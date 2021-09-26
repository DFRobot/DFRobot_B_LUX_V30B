# DFRobot_B_LUX_V30B
- [English Version](./README.md)

这款环境光传感器设计新颖，外壳采用透明的半球封装形式，可以更好的聚光而采集光照。该传感器拥有0-200klx的检测范围，采用IIC通信，针对人眼对环境光的响应，结合红外和紫外屏蔽，优化了片上光电二极管的光谱响应，自适应增益电路自动选择正确的流明范围优化测试(计数值/流明)。可用于智能灯、汽车智能灯、智能孵化器、农业、仪器仪表等。

![](./resources/images/SEN0390.png)

## 产品链接(https://www.dfrobot.com.cn/goods-2990.html)

    SKU：SEN0390

## 目录

* [概述](#概述)
* [库安装](#库安装)
* [方法](#方法)
* [兼容性](#兼容性y)
* [历史](#历史)
* [创作者](#创作者)

## 概述

- 这是一个感知光强度的传感器。
- 通过IIC传输采集到的数据，IIC地址不可更改。
- 您可以将所需的配置写入配置寄存器(地址:0x04)，设置不同的采集精度。
- 您可以从数据寄存器(地址:0x00~0x03)读取光强度数据。

## 库安装

使用此库前，请首先下载库文件，将其粘贴到\Arduino\libraries目录中，然后打开examples文件夹并在该文件夹中运行演示。

## 方法

```C++
  /**
   * @brief The constructor
   * @param cEN Optional pin
   * @param scl Clock line, specified by default as SCL
   * @param sda Data line, specified by default as SCL
   */
  DFRobot_B_LUX_V30B(uint8_t cEN, uint8_t scl = SCL, uint8_t sda = SDA);
/**
   * @brief The destructor
   */
  ~DFRobot_B_LUX_V30B(){
  };
  /**
   * @brief Initialization function
   */
  void begin(void);
  /**
   * @brief Get the intensity of light.
   * @return Returns the obtained light intensity value on success and -1 on failure
   */
  float lightStrengthLux(void);
  /**
   * @brief Set the acquisition mode of the sensor
   * @param mode Patterns that need to be configured
   * @return Returns 1 on success and -1 on failure
   */
  uint8_t setMode(uint8_t isManualMode=0,uint8_t isCDR=0,uint8_t isTime=0);
  /**
   * @brief Get the acquisition mode of the sensor
   * @return Current sensor acquisition mode
   */
  uint8_t readMode(void);
  
```

## 兼容性

|     主板      |   通过     |   未通过   |   未测试  |   备注  |
| ------------- |:---------:|:----------:|:--------:|:--------|
| Arduino uno   |     √     |            |          |         |
| Mega2560      |     √     |            |          |         |
| ESP32         |     √     |            |          |         |


## 历史

- 日期 2021-9-26
- 版本 V1.0.0


## 创作者

Written by yangfeng(feng.yang@dfrobot.com), 2021. (Welcome to our [website](https://www.dfrobot.com/))

