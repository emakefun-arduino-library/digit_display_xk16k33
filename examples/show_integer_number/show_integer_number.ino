/**
 * @example show_integer_number.ino
 * @brief 显示整数
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
  digital_display.ShowNumber(9876);  // 显示数值9876，默认为10进制
  delay(1000);

  digital_display.ShowNumber(-123);  // 显示数值-123，默认为10进制
  delay(1000);

  digital_display.ShowNumber(1000,
                             DigitDisplay::kHex);  // 显示数值1000，指定以16进制（DigitDisplay::kHex）显示
  delay(1000);

  digital_display.ShowNumber(0xabcd, DigitDisplay::kHex);  // 显示数值0xABCD，指定以16进制（DigitDisplay::kHex）显示
  delay(1000);

  digital_display.ShowNumber(10000);  // 显示整数部分超过4位的数值，将无法正常显示，会显示"----"
  delay(1000);

  digital_display.Clear();  // 清空显示内容
}