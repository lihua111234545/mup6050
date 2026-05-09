#ifndef __MPU6050_H_
#define __MPU6050_H_

#include "main.h"
#include "i2c.h"
#define MPU6050_ADDR 0x68<<1
#define PWR_MGMT_1 0x6B
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
extern float roll,pitch,yaw;
#define M_PI 3.14159265358979323846
typedef struct {
  int16_t Accel_X;
  int16_t Accel_Y;
  int16_t Accel_Z;
  int16_t Gyro_X;
  int16_t Gyro_Y;
  int16_t Gyro_Z;
  int16_t Temp;
}MPU6050_Data;

typedef struct {
  float Accel_X;
  float Accel_Y;
  float Accel_Z;
  float Gyro_X;
  float Gyro_Y;
  float Gyro_Z;
  float Temp;
}MPU6050_Change_Data;

void MPU6050_Init(I2C_HandleTypeDef *hi2c);
void MPU6050_read(I2C_HandleTypeDef *hi2c,MPU6050_Data *data);
void MPU6050_data_change(MPU6050_Data *data,MPU6050_Change_Data *change);
void Calculat_Read(MPU6050_Change_Data *change);
//void Calculat_Init(MPU6050_Change_Data *change);
void mpu6050_proc(void);
#endif
