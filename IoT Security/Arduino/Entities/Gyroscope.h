#ifndef SENSOR_H
#define SENSOR_H
#include "Sensor.h"
#endif
#include "Arduino.h"
#include <Wire.h>

class Gyroscope : Sensor
{
public:
    const int MPU_addr = 0x68; // I2C address of the MPU-6050

    void setup()
    {
        Wire.begin();
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x6B);
        Wire.write(0); // set zero (wakes up the MPU-6050
        Wire.endTransmission(true);
        TWCR = 0;
    }
    
    void measureValue(char *value)
    {
        value[0] = '\0';
        short AcX, AcY, Tmp, AcZ, Temp, GyX, GyY, GyZ;
        Wire.beginTransmission(MPU_addr);
        Wire.write(0x3B);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU_addr, 14, true); // request a total of 14 registers
        AcX = Wire.read() << 8 | Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
        AcY = Wire.read() << 8 | Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
        AcZ = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
        Temp = Wire.read() << 8 | Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
        GyX = Wire.read() << 8 | Wire.read(); // 0x43 (GYRO_XOUT_H) & 0x44 (GYRO_XOUT_L)
        GyY = Wire.read() << 8 | Wire.read(); // 0x45 (GYRO_YOUT_H) & 0x46 (GYRO_YOUT_L)
        GyZ = Wire.read() << 8 | Wire.read(); // 0x47 (GYRO_ZOUT_H) & 0x48 (GYRO_ZOUT_L)
        int StrLen = sprintf(value, "GYR:GyX=%d;GyY=%d;GyZ=%d;AcX=%d;AcY=%d;AcZ=%d", GyX, GyY, GyZ, AcX, AcY, AcZ);
        value[StrLen] = '\0';
    }
};