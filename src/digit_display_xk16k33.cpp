#include "digit_display_xk16k33.h"

namespace emakefun {

namespace {
constexpr uint8_t kNumberValues[] = {
    0x3F, /* 0 */
    0x06, /* 1 */
    0x5B, /* 2 */
    0x4F, /* 3 */
    0x66, /* 4 */
    0x6D, /* 5 */
    0x7D, /* 6 */
    0x07, /* 7 */
    0x7F, /* 8 */
    0x6F, /* 9 */
    0x77, /* a */
    0x7C, /* b */
    0x39, /* C */
    0x5E, /* d */
    0x79, /* E */
    0x71, /* F */
};
constexpr uint8_t kColonAddress = 0x04;
constexpr uint8_t kDigitlAddress[] = {0x08, 0x06, 0x02, 0x00};
};  // namespace

Xk16k33::ErrorCode DigitDisplayXk16k33::Initialize() {
  Xk16k33::ErrorCode error_code = kOK;
  error_code = Xk16k33::Initialize();
  if (error_code != kOK) {
    return error_code;
  }
  error_code = SetBlinkRate(emakefun::Xk16k33::kBlinkOff);
  if (error_code != kOK) {
    return error_code;
  }
  error_code = SetBrightness(emakefun::Xk16k33::kMaxBrightness);
  if (error_code != kOK) {
    return error_code;
  }

  error_code = Display();
  return error_code;
}

void DigitDisplayXk16k33::Clear() {
  memset(data_, sizeof(data_), 0x00);
  colon_ = false;
}

void DigitDisplayXk16k33::ShowColon(const bool on) {
  colon_ = on;
}

void DigitDisplayXk16k33::ShowDigitNumber(const uint8_t pos, const uint8_t num, const bool dot) {
  data_[pos] = kNumberValues[num] | (dot << 7);
}

void DigitDisplayXk16k33::ShowSegment(const uint8_t pos, const uint8_t value, const bool on) {
  if (on) {
    data_[pos] |= value;
  } else {
    data_[pos] &= ~value;
  }
}

bool DigitDisplayXk16k33::ShowNumber(double value, const uint8_t base, uint8_t fractional_part_digits) {
  uint8_t numeric_digits = kDigitNumber;  // available digits on display

  bool is_negative = false;
  if (value < 0) {
    --numeric_digits;
    value = -value;
    is_negative = true;
  }

  uint32_t limit_value = 1;
  for (uint8_t i = 0; i < numeric_digits; ++i) {
    limit_value *= base;
  }

  double to_int_factor = 1.0;
  for (uint8_t i = 0; i < fractional_part_digits; ++i) {
    to_int_factor *= base;
  }

  uint32_t display_number = value * to_int_factor + 0.5;
  while (display_number >= limit_value) {
    --fractional_part_digits;
    to_int_factor /= base;
    display_number = value * to_int_factor + 0.5;
  }

  if (to_int_factor < 1) {
    for (auto& data : data_) {
      data = 0x40;
    }
    return false;
  }

  int8_t position = 0;

  for (uint8_t i = 0; i <= fractional_part_digits || display_number > 0 || position == 0; i++) {
    const bool display_decimal = (fractional_part_digits != 0 && i == fractional_part_digits);
    data_[position++] = kNumberValues[display_number % base] | (display_decimal << 7);
    display_number /= base;
  }

  if (is_negative) {
    data_[position++] = 0x40;
  }
  // clear remaining display positions
  while (position < kDigitNumber) {
    data_[position++] = 0x00;
  }

  return true;
}

Xk16k33::ErrorCode DigitDisplayXk16k33::Display() {
  for (uint8_t i = 0; i < kDigitNumber; i++) {
    Write(kDigitlAddress[i], data_[i]);
  }

  return Write(kColonAddress, colon_ ? 0xFF : 0x00);
}

};  // namespace emakefun