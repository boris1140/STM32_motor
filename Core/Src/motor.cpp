//
// Created by zbxboris on 10/3/2025.
//
#include "main.h"
#include "math.h"
#include "motor.h"

float LinearMapping(const int16_t in, const int16_t in_min, const int16_t in_max, const float out_min,
                    const float out_max) {
    return (out_min + static_cast<float>(in - in_min) * (out_max - out_min) / static_cast<float>(in_max - in_min));
}

void M3508_Motor::canRxMsgCallback(const uint8_t rx_data[8]) {
    last_ecd_angle_ = ecd_angle_;
    const int16_t ecd_angle = static_cast<int16_t>((rx_data[0] << 8) + rx_data[1]);
    ecd_angle_ = LinearMapping(ecd_angle, 0.f, 8191.f, 0.f, 360.f);
    delta_ecd_angle = ecd_angle_ - last_ecd_angle_;
    if (delta_ecd_angle > 180.f) {
        delta_ecd_angle -= 360.f;
    } else if (delta_ecd_angle < -180.f) {
        delta_ecd_angle += 360.f;
    }
    delta_angle_ = delta_ecd_angle / ratio_;
    angle_ = fmodf((angle_ + delta_angle_), 360.f);
    rotate_speed_ = static_cast<float>((rx_data[2] << 8) + rx_data[3]) * 360.f / 60;
    temp_ = static_cast<float>(rx_data[6]);
    const int16_t current = static_cast<int16_t>(
        (static_cast<uint16_t>(rx_data[4]) << 8) | static_cast<uint16_t>(rx_data[5]));
    current_ = LinearMapping(current, -16384.f, 16384.f, -20.f, 20.f);
}
