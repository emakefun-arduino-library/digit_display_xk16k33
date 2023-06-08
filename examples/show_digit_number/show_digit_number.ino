/**
 * @example show_digit_number.ino
 * @brief 按位置显示数字
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
  digital_display.ShowDigitNumber(0, 1, false);  // 第0位显示1
  digital_display.ShowDigitNumber(1, 2, true);   // 第1位显示2.
  digital_display.ShowDigitNumber(2, 3, false);  // 第2位显示3
  digital_display.ShowDigitNumber(3, 4, true);   // 第3位显示4.
  delay(500);

  digital_display.Clear();  // 清空显示内容
  delay(500);
}