#include "pid.h"
#include <algorithm>

PID::PID(float kp, float ki, float kd, float i_max, float out_max, float d_filter_k)
    : kp_(kp), ki_(ki), kd_(kd), d_filter_k_(d_filter_k),
      i_max_(i_max), out_max_(out_max) {
    reset();
}

void PID::reset(void) {
    ref_ = fdb_ = err_ = err_sum_ = last_err_ = 0;
    pout_ = iout_ = dout_ = last_dout_ = output_ = 0;
}

float PID::calc(float ref, float fdb) {
    ref_ = ref;
    fdb_ = fdb;
    err_ = ref_ - fdb_;

    pout_ = kp_ * err_;
    err_sum_ += err_;
    err_sum_ = std::clamp(err_sum_, -i_max_, i_max_);
    iout_ = ki_ * err_sum_;

    float d_err = err_ - last_err_;
    dout_ = d_filter_k_ * last_dout_ + (1 - d_filter_k_) * (kd_ * d_err);
    last_dout_ = dout_;
    last_err_ = err_;

    output_ = pout_ + iout_ + dout_;
    output_ = std::clamp(output_, -out_max_, out_max_);
    return output_;
}
