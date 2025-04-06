/*
 * File: sensor_fusion.h
 * Author: Rick Hayes
 * License: MIT
 * Version: 1.3
 * Date: April 05, 2025
 */
#ifndef SENSOR_FUSION_H
#define SENSOR_FUSION_H

class SensorFusion {
private:
    float kalmanGain = 0.5f;
    float estimate = 0.0f;
public:
    float update(float measurement) {
        estimate = estimate + kalmanGain * (measurement - estimate);
        return estimate;
    }
    void reset() { estimate = 0.0f; }
};

#endif // SENSOR_FUSION_H
