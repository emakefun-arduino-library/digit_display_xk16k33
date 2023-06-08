/**
 * @example show_decimal_number.ino
 * @brief 显示小数
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
  digital_display.ShowNumber(12.34);  // 显示小数12.34，默认显示两位小数，超出部分将会被四舍五入
  delay(1000);

  digital_display.ShowNumber(-12.34);  // 显示小数-12.34，默认显示两位小数，超出部分将会被四舍五入
  delay(1000);

  digital_display.ShowNumber(12.34, 1);  // 显示小数12.34，指定显示一位小数，超出部分将会被四舍五入
  delay(1000);

  digital_display.ShowNumber(12.34,
                             DigitDisplay::kHex);  // 显示小数12.34，默认显示两位小数，超出部分将会被四舍五入，指定以16进制显示
  delay(1000);

  digital_display.ShowNumber(
      12.34, DigitDisplay::kHex, 1);  // 显示小数12.34，指定显示一位小数，超出部分将会被四舍五入，指定以16进制显示
  delay(1000);

  digital_display.ShowNumber(9999.99);  // 进位后整数部分超过4位的数值，将无法正常显示，会显示"----"
  delay(1000);

  digital_display.Clear();  // 清空显示内容
}