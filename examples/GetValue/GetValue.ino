/*
    Description: Use Pbhub to read the analog input value of the slave device,
   or drive multiple sets of RGB LEDs.
*/

#include <M5Stack.h>
#include <Wire.h>
#include "MODULE_HMI.h"
#include <M5GFX.h>

M5GFX display;
M5Canvas canvas(&display);
MODULE_HMI hmi_module;

#define M5BUS_DELAY_TIME 100

unsigned long end_time = 0;
uint16_t delay_time    = 0;
uint8_t led1_status    = 0;
uint8_t led2_status    = 0;
int32_t inc_count      = 0;

void setup() {
    M5.begin(true, false, true, false);
    M5.Power.begin();
    display.begin();
    canvas.setColorDepth(8);  // mono color
    canvas.setFont(&fonts::efontCN_12);
    canvas.createSprite(display.width(), display.height());
    hmi_module.begin(&Wire, HMI_ADDR, 21, 22, 100000);

    end_time = millis();
}

void loop() {
    M5.update();
    if (M5.BtnA.wasPressed()) {
        if (led1_status) {
            hmi_module.setLEDStatus(0, 0);
            led1_status = 0;
        } else {
            hmi_module.setLEDStatus(0, 1);
            led1_status = 1;
        }
    } else if (M5.BtnB.wasPressed()) {
        if (led2_status) {
            hmi_module.setLEDStatus(1, 0);
            led2_status = 0;
        } else {
            hmi_module.setLEDStatus(1, 1);
            led2_status = 1;
        }
    }
    if (M5.BtnC.wasReleasefor(100)) {
        hmi_module.resetCounter();
    }
    if (M5.BtnC.pressedFor(1000)) {
        while (M5.BtnC.read())
            ;
        inc_count = hmi_module.getIncrementValue();
    }

    canvas.fillSprite(BLACK);
    canvas.setTextSize(2);
    canvas.setCursor(100, 0);
    canvas.setTextColor(YELLOW);
    canvas.printf("HMI Test");
    canvas.setTextColor(ORANGE);
    canvas.drawLine(25, 25, 310, 25);
    canvas.setCursor(0, 30);
    canvas.printf("Encoder value: %d", hmi_module.getEncoderValue());
    canvas.setCursor(0, 60);
    canvas.printf("Encoder inc value: %d", inc_count);
    canvas.setCursor(0, 90);
    canvas.printf("btnS:%d, btnA:%d, btnB:%d", hmi_module.getButtonS(),
                  hmi_module.getButton1(), hmi_module.getButton2());
    canvas.drawString("Led1", 40, 220);
    canvas.drawString("Led2", 130, 220);
    canvas.drawString("reset/inc", 210, 220);

    canvas.pushSprite(0, 0);
}