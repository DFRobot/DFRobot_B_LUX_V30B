/*!
 * @file DFRobot_B_LUX_V30B.h
 * @brief Define a class of DFRobot_B_LUX_V30B.
 * @n This is a sensor that gets the intensity of light.
 * @n It uses IIC to transmit the collected data, and its IIC address cannot be changed.
 * @n You can write the desired configuration to the configuration register(address:0x04), setting different acquisition accuracy.
 * @n You can read the light intensity data from the data register(address:0x00~0x03).
 * @copyright	Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @licence     The MIT License (MIT)
 * @author [Fary](Fary_young@outlook.com)
 * @version  V1.0
 * @date  2020-12-03
 * @https://github.com/DFRobot/DFRobot_B_LUX_V30B
 */
#ifndef  _DFROBOT_B_LUX_V30B_H_
#define  _DFROBOT_B_LUX_V30B_H_

#include <Arduino.h>

#define ENABLE_DBG

#ifdef ENABLE_DBG
#define DBG(...)  {\
                  Serial.print("[");\
                  Serial.print(__FUNCTION__);\
                  Serial.print("(): ");\
                  Serial.print(__LINE__);\
                  Serial.print(" ] ");\
                  Serial.println(__VA_ARGS__);\
                  }
#else
#define DBG(...)
#endif

#define DFRobot_B_LUX_V30_IIC_Addr  0x94   //the address of IIC

#define DFRobot_B_LUX_V30_DataReg        0x00   //the address of the data register
#define DFRobot_B_LUX_V30_ConfigReg      0x04   //the address of the configuration register
typedef unsigned int    uint;
class DFRobot_B_LUX_V30B{
public:
  #define ACK        0x00
  #define NACK       0x01
  
  /*
   The description of this register is copied from the data sheet
     * ------------------------------------------------------------------------------------------
     * |    b7    |    b6    |    b5    |    b4    |    b3    |    b2    |    b1     |    b0    |
     * ------------------------------------------------------------------------------------------
     * |    0     |  MANUAL  |    0     |     0    |    CDR   |               TIM               |
     * ------------------------------------------------------------------------------------------
     *MANUAL  ：Manual configuration register.
                0 represents the default automatic mode.In this mode ,CDR and TIM are automatically assigned.
     *          1 represents the configuration of manual mode.In this mode,CDR and TIM can be set by the user.
     *CDR     ：Shunt ratio register.
     *          0 represents the default of not dividing,all the current of the photodiode into the ADC
     *          1 represents the division of 8,as long as 1/8 of the current of the photodiode changes to ADC. This mode is used in high brightness situations.
     *TIM[2:0]：Acquisition time.
     *        ------------------------------------------------------------------------------------------------
     *          TIM[2:0]  |  TIME（ms）  |                          Introduction                             |
     *        ------------------------------------------------------------------------------------------------
     *             000    |      800     |            Preferred mode in low light environment                |
     *        ------------------------------------------------------------------------------------------------
     *             001    |      400     |                               ---                                 |
     *        ------------------------------------------------------------------------------------------------
     *             010    |      200     |                               ---                                 |
     *        ------------------------------------------------------------------------------------------------
     *             011    |      100     |   In the strong light environment, select the mode preferentially |
     *        ------------------------------------------------------------------------------------------------
     *             100    |      50      |                       Manual mode only                            |
     *        ------------------------------------------------------------------------------------------------
     *             101    |      250     |                       Manual mode only                            |
     *        ------------------------------------------------------------------------------------------------
     *             110    |      12.5    |                       Manual mode only                            |
     *        ------------------------------------------------------------------------------------------------
     *             111    |      6.25    |                       Manual mode only                            |
     *        ------------------------------------------------------------------------------------------------
     *Accuracy that can be set in manual mode:
     *     -------------------------------------------------------------------------------------------------------------
     *     |                    Light conditions                        |                        |     TIM & CDR       |
     *     -------------------------------------------------------------------------------------------------------------
     *     |   Minimum accuracy    |   Maximum accuracy   |   Maximum   |  Acquisition time(ms)  |    TIM     |   CDR  |
     *     —------------------------------------------------------------------------------------------------------------
     *              0.054                     11.52            2938                800                000           0   
     *              0.09                      23.04            5875                400                001           0   
     *              0.18                      46.08            11750               200                010           0   
     *              0.36                      92.16            23501               100                011           0   
     *              0.36                      92.16            23501               800                000           1   
     *              0.72                      184.32           47002               50                 100           0   
     *              0.72                      184.32           47002               400                001           1   
     *              1.44                      368.64           94003               25                 101           0   
     *              1.44                      368.64           94003               200                010           1   
     *              2.88                      737.28           200000              12.5               110           0   
     *              2.88                      737.28           200000               100               011           1   
     *              5.76                      737.28           200000               6.25              111           0   
     *              5.76                      737.28           200000               50                100           1   
     *              11.52                     737.28           200000               25                101           1   
     *              23.04                     737.28           200000               12.5              110           1   
     *              46.08                     737.28           200000               6.25              111           1   
     *     —------------------------------------------------------------------------------------------------------------
  */
  typedef struct {
    uint8_t TIM :3;   
    uint8_t CDR :1;
    uint8_t BIT_4 :1;
    uint8_t BIT_5 :1;
    uint8_t MANUAL :1;  
    uint8_t BIT_7 :1;
  }__attribute__((packed)) sLightConfig_t;
  typedef enum{
    eAutomatic = 0<<6,
    eManual = 1<<6,
  }eManualMode_t;
  typedef enum{
    eCDR_0 = 0<<3,
    eCDR_1 = 1<<3,
  }eCDRMode_t;
  typedef enum{
    eTime800ms = 0,
    eTime400ms = 1,
    eTime200ms = 2,
    eTime100ms = 3,
    eTime50ms = 4,
    eTime25ms = 5,
    eTime12_5ms = 6,
    eTime6_25ms = 7,
  }eTimeMode_t;

public:
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
  
private:
  /**
   * @brief IIC start signal
   */
  void iicStartBit(void);
  /**
   * @brief IIC stop signal
   */
  void iicStopBit(void);
  /**
   * @brief The IIC host sends a reply
   */
  void iicSendAck(uint8_t ack);
  /**
   * @brief The IIC host receive a reply
   * @return The value of SDA in the current period
   */
  uint8_t iicRecvAck(void);
  /**
   * @brief Send a byte of data
   * @param data The data that needs to be sent can be either a register address or data
   * @return A return value of 0 represents ACK, and a return value of 1 represents NACK
   */
  uint8_t iicSend(uint8_t data);
  /**
   * @brief Receive a byte of data
   * @return A return value of 0 represents ACK, and a return value of 1 represents NACK
   */
  uint8_t iicReadByte();

  /**
   * @brief IIC read operation
   * @param num The number of registers to read
   * @param *data The address of the data to be received
   * @return Returns 1 on success and -1 on failure
   */
  uint8_t iicRead(uint8_t num, uint8_t* data);

private:
  uint8_t _SDA;
  uint8_t _SCL;
  uint8_t _cEN;
  uint8_t _deviceAddr;
};
#endif




















