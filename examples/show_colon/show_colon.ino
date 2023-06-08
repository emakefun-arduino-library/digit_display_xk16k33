/**
 * @example show_colon.ino
 * @brief 显示/隐藏冒号
 */

#include <Arduino.h>
#include <Wire.h>

// 包含头文件: digit_display.h
#include "digit_display.h"

// 初始化DigitDisplay，i2c地址为：0x70 (DigitDisplay::kDeviceI2cAddress)
DigitDisplay digital_display(DigitDisplay::kDeviceI2cAddress);

void setup() {
  Serial.begin(115200);
  digital_display.Setup();            // 初始化，会清空显示内容
  digital_display.SetBrightness(15);  // 设置亮度为15，范围0 ~ 15，数值越大越亮
}

void loop() {
  digital_display.ShowColon(true);   // 显示冒号
  digital_display.ShowNumber(1234);  // 显示1234
  delay(500);

  digital_display.ShowColon(false);  // 隐藏冒号
  delay(500);
}