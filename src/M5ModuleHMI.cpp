#include "M5ModuleHMI.h"

void M5ModuleHMI::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length)
{
    _wire->beginTransmission(addr);
    _wire->write(reg);
    for (int i = 0; i < length; i++) {
        _wire->write(*(buffer + i));
    }
    _wire->endTransmission();
}

void M5ModuleHMI::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer, uint8_t length)
{
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission(false);
    _wire->requestFrom(addr, length);
    for (int i = 0; i < length; i++) {
        buffer[index++] = _wire->read();
    }
}

bool M5ModuleHMI::begin(TwoWire *wire, uint8_t addr, uint8_t sda, uint8_t scl, uint32_t speed)
{
    _wire  = wire;
    _addr  = addr;
    _sda   = sda;
    _scl   = scl;
    _speed = speed;
    _wire->begin(_sda, _scl, _speed);
    delay(10);
    _wire->beginTransmission(_addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        return true;
    } else {
        return false;
    }
}

int32_t M5ModuleHMI::getEncoderValue()
{
    uint8_t data[4];
    readBytes(_addr, ENCODER_REG, data, 4);
    int32_t value = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
    return value;
}

int32_t M5ModuleHMI::getIncrementValue()
{
    uint8_t data[4];
    readBytes(_addr, INCREMENT_REG, data, 4);
    int32_t value = data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
    return value;
}

bool M5ModuleHMI::getButtonS()
{
    uint8_t data;
    readBytes(_addr, BUTTON_REG, &data, 1);
    return data;
}

bool M5ModuleHMI::getButton1()
{
    uint8_t data;
    readBytes(_addr, BUTTON_REG + 1, &data, 1);
    return data;
}

bool M5ModuleHMI::getButton2()
{
    uint8_t data;
    readBytes(_addr, BUTTON_REG + 2, &data, 1);
    return data;
}

void M5ModuleHMI::setLEDStatus(uint8_t index, uint8_t status)
{
    uint8_t data[4];
    uint8_t reg = LED_REG + index;
    data[0]     = status;
    writeBytes(_addr, reg, data, 1);
}

uint8_t M5ModuleHMI::getLEDStatus(uint8_t index)
{
    uint8_t data[4];
    uint8_t reg = LED_REG + index;
    readBytes(_addr, reg, data, 1);
    return data[0];
}

void M5ModuleHMI::resetCounter(void)
{
    uint8_t data[4];
    data[0] = 1;
    writeBytes(_addr, RESET_COUNTER_REG, data, 1);
}

uint8_t M5ModuleHMI::setI2CAddress(uint8_t addr)
{
    _wire->beginTransmission(_addr);
    _wire->write(I2C_ADDRESS_REG);
    _wire->write(addr);
    _wire->endTransmission();
    _addr = addr;
    return _addr;
}

uint8_t M5ModuleHMI::getI2CAddress(void)
{
    _wire->beginTransmission(_addr);
    _wire->write(I2C_ADDRESS_REG);
    _wire->endTransmission();

    uint8_t RegValue;

    _wire->requestFrom(_addr, 1);
    RegValue = Wire.read();
    return RegValue;
}

uint8_t M5ModuleHMI::getFirmwareVersion(void)
{
    _wire->beginTransmission(_addr);
    _wire->write(FIRMWARE_VERSION_REG);
    _wire->endTransmission();

    uint8_t RegValue;

    _wire->requestFrom(_addr, 1);
    RegValue = Wire.read();
    return RegValue;
}
