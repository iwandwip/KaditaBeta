/*
 *  sensor-filter.h
 *
 *  sensor filter lib
 *  Created on: 2023. 4. 3
 */

#pragma once

#ifndef SENSOR_FILTER_H
#define SENSOR_FILTER_H

#include "Arduino.h"

class KalmanFilter {
private:
    float _err_measure;
    float _err_estimate;
    float _q;
    float _current_estimate = 0;
    float _last_estimate = 0;
    float _kalman_gain = 0;
public:
    KalmanFilter(float mea_e, float est_e, float q);
    float updateEstimate(float mea);
    void setMeasurementError(float mea_e);
    void setEstimateError(float est_e);
    void setProcessNoise(float q);
    float getKalmanGain();
    float getEstimateError();
};

#endif  // SENSOR_FILTER_H
