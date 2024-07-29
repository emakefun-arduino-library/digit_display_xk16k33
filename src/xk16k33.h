#pragma once

#ifndef EMAKEFUN_XK16K33_H_
#define EMAKEFUN_XK16K33_H_

#include <Wire.h>
#include <stdint.h>

namespace emakefun {
class Xk16k33 {
 public:
  static constexpr uint8_t kDefaultI2cAddress = 0x70;
  static constexpr uint8_t kMaxBrightness = 15;
  /**
   * @enum ErrorCode
   * @brief 错误码
   */
  enum ErrorCode : uint32_t {
    kOK = 0,                                  /**< 0：成功 */
    kI2cDataTooLongToFitInTransmitBuffer = 1, /**< 1：I2C数据太长，无法装入传输缓冲区 */
    kI2cReceivedNackOnTransmitOfAddress = 2,  /**< 2：在I2C发送地址时收到NACK */
    kI2cReceivedNackOnTransmitOfData = 3,     /**< 3：在I2C发送数据时收到NACK */
    kI2cOtherError = 4,                       /**< 4：其他I2C错误 */
    kI2cTimeout = 5,                          /**< 5：I2C通讯超时 */
    kInvalidParameter = 6,                    /**< 6：参数错误 */
    kUnknownError = 7,                        /**< 7：未知错误*/
  };

  /**
   * @cond English
   * @brief Blink rate enumeration
   * @endcond
   * @cond Chinese
   * @brief 闪烁频率枚举
   * @endcond
   */
  enum BlinkRate : uint8_t {
    /**
     * @cond English
     * Turn off blinking
     * @endcond
     * @cond Chinese
     * 关闭闪烁
     * @endcond
     */
    kBlinkOff = 0,
    /**
     * @cond English
     * Blink rate 2Hz
     * @endcond
     * @cond Chinese
     * 闪烁频率2Hz
     * @endcond
     */
    kBlinkRate2Hz = 1,
    /**
     * @cond English
     * Blink rate 1Hz
     * @endcond
     * @cond Chinese
     * 闪烁频率1Hz
     * @endcond
     */
    kBlinkRate1Hz = 2,
    /**
     * @cond English
     * Blink rate 0.5Hz
     * @endcond
     * @cond Chinese
     * 闪烁频率0.5Hz
     * @endcond
     */
    kBlinkRateHalfHz = 3,
  };

  explicit Xk16k33(const uint8_t i2c_address = kDefaultI2cAddress, TwoWire& wire = Wire);

  explicit Xk16k33(TwoWire& wire) : Xk16k33(kDefaultI2cAddress, wire) {
  }

  /**
   * @brief 初始化函数
   * @return 返回值请参考 @ref ErrorCode
   */
  ErrorCode Initialize();
  ErrorCode SetBlinkRate(const BlinkRate blink_rate);
  ErrorCode SetBrightness(uint8_t brightness);
  ErrorCode Write(const uint8_t* data, const size_t length);
  ErrorCode Write(const uint8_t address, const uint8_t value);
  ErrorCode Write(const uint8_t address, const uint8_t* data, const size_t length);

 private:
  Xk16k33(const Xk16k33&) = delete;
  Xk16k33& operator=(const Xk16k33&) = delete;

  const uint8_t i2c_address_ = kDefaultI2cAddress;
  TwoWire& wire_ = Wire;
};
}  // namespace emakefun
#endif