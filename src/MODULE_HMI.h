#ifndef __MODULE_HMI_H
#define __MODULE_HMI_H

#include "Arduino.h"
#include "Wire.h"

#define HMI_ADDR             0x41
#define ENCODER_REG          0x00
#define INCREMENT_REG        0x10
#define BUTTON_REG           0x20
#define LED_REG              0x30
#define RESET_COUNTER_REG    0x40
#define FIRMWARE_VERSION_REG 0xFE
#define I2C_ADDRESS_REG      0xFF

class MODULE_HMI {
   private:
    uint8_t _addr;
    TwoWire* _wire;
    uint8_t _scl;
    uint8_t _sda;
    uint8_t _speed;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);

   public:
    bool begin(TwoWire* wire = &Wire, uint8_t addr = HMI_ADDR, uint8_t sda = 21,
               uint8_t scl = 22, uint32_t speed = 100000L);
    int32_t getEncoderValue();
    int32_t getIncrementValue();
    bool getButtonS();
    bool getButton1();
    bool getButton2();
    void setLEDStatus(uint8_t index, uint8_t status);
    uint8_t getLEDStatus(uint8_t index);
    uint8_t setI2CAddress(uint8_t addr);
    uint8_t getI2CAddress(void);
    uint8_t getFirmwareVersion(void);
    void resetCounter(void);
};

#endif
