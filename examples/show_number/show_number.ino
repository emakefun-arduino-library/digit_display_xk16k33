/**
 * @example show_segment.ino
 */

#include "digit_display_xk16k33.h"

#define INFINITE_LOOP_ON_FAILURE InfiniteLoopOnFailure(__FUNCTION__, __LINE__)

namespace {

emakefun::DigitDispalyXk16k33 g_digital_display;

void InfiniteLoopOnFailure(const char* function, const uint32_t line_number) {
  Serial.println(String(F("entering an infinite loop due to failure in ")) + function + F(", at line number: ") + line_number);
  while (true) {
    yield();
  }
}

}  // namespace

void setup() {
  Serial.begin(115200);
  Serial.println(F("setup"));

  Wire.begin();

  const auto ret = g_digital_display.Initialize();

  if (emakefun::Xk16k33::kOK == ret) {
    Serial.println(F("i2c device initialization successful"));
  } else {
    Serial.print(F("i2c device initialization failed: "));
    Serial.println(ret);
    INFINITE_LOOP_ON_FAILURE;
  }

  g_digital_display.SetBrightness(emakefun::Xk16k33::kMaxBrightness);

  Serial.println(F("setup successful"));
}

void loop() {
  const int int_value = 1234;
  g_digital_display.ShowNumber(int_value);
  g_digital_display.Dispaly();
  delay(1000);

  const float float_value = 23.45;
  g_digital_display.ShowNumber(float_value);
  g_digital_display.Dispaly();
  delay(1000);

  const double double_value = -1.23;
  g_digital_display.ShowNumber(double_value);
  g_digital_display.Dispaly();
  delay(1000);

  const int large_value = 99999;
  g_digital_display.ShowNumber(large_value);
  g_digital_display.Dispaly();
  delay(1000);
}
