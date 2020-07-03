#ifndef ESTIMATOR_H
#define ESTIMATOR_H

#include "IMU6050Driver.h"

void getAcceleroRads(float *data, MPU6050 *IMU)
{
    float temp[3];
    IMU->getAccelero(temp);

    data[X_AXIS] =
        atan(temp[Y_AXIS] /
             sqrt(pow(temp[X_AXIS], 2) +
                  pow(temp[Z_AXIS], 2))); // calculate angle x(pitch/roll?) from
                                          // accellerometer reading
    data[Y_AXIS] =
        atan(-1 * temp[X_AXIS] /
             sqrt(pow(temp[Y_AXIS], 2) +
                  pow(temp[Z_AXIS], 2))); // calculate angle x(pitch/roll?) from
                                          // accellerometer reading
    data[Z_AXIS] = atan(sqrt(pow(temp[X_AXIS], 2) + pow(temp[Y_AXIS], 2)) /
                        temp[Z_AXIS]); // This one is not used anywhere later on
}

/// function for getting offset values for the gyro & accelerometer
void getOffset(float *accOffset, float *gyroOffset, int sampleSize,
               MPU6050 *IMU)
{
    float gyro[3];
    float accAngle[3];

    for (int i = 0; i < 3; i++)
    {
        accOffset[i] = 0.0; // initialise offsets to 0.0
        gyroOffset[i] = 0.0;
    }

    for (int i = 0; i < sampleSize; i++)
    {
        IMU->getGyro(gyro);
        getAcceleroRads(accAngle, IMU);

        for (int j = 0; j < 3; j++)
        {
            *(accOffset + j) +=
                accAngle[j] / sampleSize; // average measurements
            *(gyroOffset + j) += gyro[j] / sampleSize;
        }
    }
}

/// function for computing angles for roll, pitch anf yaw
void computeAngle(float *angle, float *accOffset, float *gyroOffset,
                  float interval, float alpha, MPU6050 *IMU)
{
    float gyro[3];
    float accAngle[3];

    IMU->getGyro(gyro);             // get gyro value in rad/s
    getAcceleroRads(accAngle, IMU); // get angle from accelerometer

    for (int i = 0; i < 3; i++)
    {
        gyro[i] -= gyroOffset[i]; // substract offset values
        accAngle[i] -= accOffset[i];
    }

    // apply filters on pitch and roll to get accurate angle values
    angle[X_AXIS] =
        alpha * (angle[X_AXIS] + GYRO_SCALE * gyro[X_AXIS] * interval) +
        (1 - alpha) * accAngle[X_AXIS];
    angle[Y_AXIS] =
        alpha * (angle[Y_AXIS] + GYRO_SCALE * gyro[Y_AXIS] * interval) +
        (1 - alpha) * accAngle[Y_AXIS];

    // calculate Yaw using just the gyroscope values - inaccurate
    angle[Z_AXIS] = accAngle[Z_AXIS] + GYRO_SCALE * gyro[Z_AXIS] * interval;
}

#endif