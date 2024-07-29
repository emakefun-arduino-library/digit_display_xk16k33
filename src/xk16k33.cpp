#include "xk16k33.h"

namespace {
constexpr uint8_t kCmdBlink = 0x80;
constexpr uint8_t kCmdBrightness = 0xE0;
constexpr uint8_t kBlinkDisplayOn = 0x01;

// #define HT16K33_CMD_BLINK (0x80)         ///< I2C register for BLINK setting
// #define HT16K33_BLINK_DISPLAY_ON (0x01)  ///< I2C value for steady on
// #define HT16K33_CMD_BRIGHTNESS (0xE0)    ///< I2C register for BRIGHTNESS setting

// #define DIGIT_NUMBER (4)
// #define COLON_BUFFER_POSITION (2)
}  // namespace

namespace emakefun {

Xk16k33::Xk16k33(const uint8_t i2c_address, TwoWire& wire) : i2c_address_(i2c_address), wire_(wire) {
  // do somethings
}

Xk16k33::ErrorCode Xk16k33::Initialize() {
  wire_.beginTransmission(i2c_address_);
  wire_.write(0x21);  // turn on oscillator
  auto ret = static_cast<ErrorCode>(wire_.endTransmission());

  const uint8_t data[16] = {0};
  return Write(data, sizeof(data));
}

Xk16k33::ErrorCode Xk16k33::SetBlinkRate(const BlinkRate blink_rate) {
  wire_.beginTransmission(i2c_address_);
  wire_.write(kCmdBlink | kBlinkDisplayOn | (blink_rate << 1));
  return static_cast<ErrorCode>(wire_.endTransmission());
}

Xk16k33::ErrorCode Xk16k33::SetBrightness(uint8_t brightness) {
  if (brightness > kMaxBrightness) {
    brightness = kMaxBrightness;
  }
  wire_.beginTransmission(i2c_address_);
  wire_.write(kCmdBrightness | brightness);
  return static_cast<ErrorCode>(wire_.endTransmission());
}

Xk16k33::ErrorCode Xk16k33::Write(const uint8_t* data, const size_t length) {
  return Write(0x00, data, length);
}

Xk16k33::ErrorCode Xk16k33::Write(const uint8_t address, const uint8_t value) {
  return Write(address, &value, 1);
}

Xk16k33::ErrorCode Xk16k33::Write(const uint8_t address, const uint8_t* data, const size_t length) {
  wire_.beginTransmission(i2c_address_);
  wire_.write(address);
  wire_.write(data, length);
  return static_cast<ErrorCode>(wire_.endTransmission());
}
}  // namespace emakefun