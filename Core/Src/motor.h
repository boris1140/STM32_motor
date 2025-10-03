//
// Created by zbxboris on 10/3/2025.
//

#ifndef MOTOR_MOTOR_H
#define MOTOR_MOTOR_H

#ifdef __cplusplus
extern "C" {
#endif
    float LinearMapping(const int16_t in, const int16_t in_min, const int16_t in_max, const float out_min,
                        const float out_max);
#ifdef __cplusplus
}
#endif


#ifdef __cplusplus

class M3508_Motor {
private:
    const float ratio_;
    float angle_ = 0.F;
    float delta_angle_ = 0.f;
    float ecd_angle_ = 0.f;
    float last_ecd_angle_ = 0.f;
    float delta_ecd_angle = 0.f;
    float rotate_speed_ = 0.f;
    float current_ = 0.f;
    float temp_ = 0.f;

public:
    explicit M3508_Motor(const float ratio) : ratio_(ratio) {
    };

    void canRxMsgCallback(const uint8_t rx_data[8]);
};

#endif

#endif //MOTOR_MOTOR_H
