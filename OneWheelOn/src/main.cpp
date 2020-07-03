
#include <IMU6050Driver.h>
#include <PID.hpp>
#include <Timestamped.hpp>
#include <estimator.h>
#include <mbed.h>
#include <motorMixer.hpp>
#include <BrushlessMotorController.h>

//Serial pc(PA_2, PA_3, 115200);

int main()
{
    // timer for calculating delta time
    Timer gyroTimer;

    // PID setup
    PIDController<float> PID;
    PID.kd = .2;
    PID.ki = 0;
    PID.kp = 1;
    float PIDOut;

    // set up IMU
    MPU6050 IMU(PB_7, PB_6);
    Timestamped<float[3]> data;
    float accelOffset[3], gyroOffset[3];
    float alpha = .96;
    int sampleSize = 10;

    getOffset(accelOffset, gyroOffset, sampleSize, &IMU);

    //motor setup
    BrushlessMotorController motor(PA_8);
    int motorMixerOut;

    gyroTimer.start();
    while (1)
    {
        // // getting accel and computing current angle
        // // result stored in data x - 1, y - 2
        getAcceleroRads(data.value, &IMU);
        data.time = gyroTimer.read();
        computeAngle(data.value, accelOffset, gyroOffset, data.time, alpha,
                     &IMU);
        gyroTimer.reset();

        // takes in current angle and goal
        PIDOut = PID.update(data.time, data.value[2], 0);

        motorMixerOut = motorMixer(PIDOut, 1.5);

        //pc.printf("%d", PIDOut);
        motor.setPulsewidth(motorMixerOut);
        motor.update();

        // wait_ms(100);
    }
}
