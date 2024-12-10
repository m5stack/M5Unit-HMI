/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#include <M5Unified.h>
#include <M5GFX.h>
#include "M5ModuleHMI.h"
#include <Wire.h>

M5ModuleHMI hmi_module;
int32_t inc_count       = 0;
int32_t current_encoder = 0;
bool button_a_status    = false;
bool button_b_status    = false;
bool button_s_status    = false;

void setup()
{
    M5.begin();
    M5.Display.setFont(&fonts::efontCN_12);
    M5.Display.setTextSize(2);

    // for Core1
    // Wire1.end();
    // hmi_module.begin(&Wire1, HMI_ADDR, 21, 22, 100000);

    // for Core2
    // Wire1.end();
    // hmi_module.begin(&Wire1, HMI_ADDR, 21, 22, 100000);

    // for CoreS3
    Wire1.end();
    hmi_module.begin(&Wire1, HMI_ADDR, 12, 11, 100000);

    hmi_module.setLEDStatus(0, 1);
    hmi_module.setLEDStatus(1, 1);

    hmi_module.resetCounter();
}

void loop()
{
    current_encoder = hmi_module.getEncoderValue();
    button_s_status = hmi_module.getButtonS();
    button_a_status = hmi_module.getButton1();
    button_b_status = hmi_module.getButton2();

    M5.Display.fillRect(0, 0, 320, 100, BLACK);
    M5.Display.setCursor(0, 0);
    M5.Display.printf("Encoder value: %d\r\n", current_encoder);
    M5.Display.printf("btnS:%d, btnA:%d, btnB:%d\r\n", button_s_status, button_a_status, button_b_status);

    delay(100);
}
