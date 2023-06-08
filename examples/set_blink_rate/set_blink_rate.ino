/**
 * @example set_blink_rate.ino
 * @brief 设置闪烁频率
 */

#include <Arduino.h>
#include <Wire.h>

// 包含头文件: digit_display.h
#include "digit_display.h"

// 初始化DigitDisplay，i2c地址为：0x70 (DigitDisplay::kDeviceI2cAddress)
DigitDisplay digital_display(DigitDisplay::kDeviceI2cAddress);

void setup() {
  Serial.begin(115200);
  digital_display.Setup();  // 初始化，会清空显示内容

  digital_display.SetBrightness(15);  // 设置亮度为15，范围0 ~ 15，数值越大越亮

  digital_display.SetBlinkRate(
      DigitDisplay::kBlinkRate2Hz);  // 开启闪烁功能并设置闪烁频率为2Hz，代表每秒闪烁两次，默认为关闭闪烁功能
}

void loop() {
  digital_display.ShowNumber(8888);  // 显示8888
}