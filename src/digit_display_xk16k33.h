
#pragma once

#ifndef EMAKEFUN_DIGITAL_DISPLAY_XK16K33_H_
#define EMAKEFUN_DIGITAL_DISPLAY_XK16K33_H_

#include "xk16k33.h"

namespace emakefun {
class DigitDispalyXk16k33 : public Xk16k33 {
 public:
  static constexpr uint8_t kDigitNumber = 4;

  enum Segment : uint8_t {
    kSegmentA = 1 << 0,
    kSegmentB = 1 << 1,
    kSegmentC = 1 << 2,
    kSegmentD = 1 << 3,
    kSegmentE = 1 << 4,
    kSegmentF = 1 << 5,
    kSegmentG = 1 << 6,
    kSegmentH = 1 << 7,
  };

  enum Base : uint8_t {
    kBin = 2,
    kOct = 8,
    kDec = 10,
    kHex = 16,
  };

  Xk16k33::ErrorCode Initialize();
  void Clear();
  void ShowColon(const bool on);
  void ShowDigitNumber(const uint8_t pos, const uint8_t num, const bool dot = false);
  void ShowSegment(const uint8_t pos, const uint8_t value, const bool on);
  template <typename T>
  bool ShowNumber(T value, const uint8_t base = kDec) {
    return ShowNumber(static_cast<double>(value), base, 0);
  }
  bool ShowNumber(float value, const uint8_t base = kDec, uint8_t fractional_part_digits = 2) {
    return ShowNumber(static_cast<double>(value), base, fractional_part_digits);
  }
  bool ShowNumber(double value, const uint8_t base = kDec, uint8_t fractional_part_digits = 2);
  Xk16k33::ErrorCode Dispaly();

 private:
  uint8_t data_[kDigitNumber] = {0};
  bool colon_ = false;
};

}  // namespace emakefun

#endif
