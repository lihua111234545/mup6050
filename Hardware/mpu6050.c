#include "MPU6050.h"
#include "math.h"


static float Roll = 0.0, Pitch = 0.0, Yaw = 0.0; // ��ʼ��ŷ����
//=====================================数据读取=====================
void MPU6050_Init(I2C_HandleTypeDef *hi2c)
{
	unsigned char data[2];
	
	//唤醒 MPU6050
	data[0]=PWR_MGMT_1;
	data[1]=0x00;
	HAL_I2C_Master_Transmit(hi2c,MPU6050_ADDR,data,2,HAL_MAX_DELAY);
	
	// 配置陀螺仪范围 (±2000°/s)
	data[0]=0x1B;
	data[1]=0x18;// ±2000°/s
	HAL_I2C_Master_Transmit(hi2c,MPU6050_ADDR,data,2,HAL_MAX_DELAY);
	
	// 配置加速度计范�? (±8g)
	data[0]=0x1C;
	data[1]=0x10;
	HAL_I2C_Master_Transmit(hi2c,MPU6050_ADDR,data,2,HAL_MAX_DELAY);
}

void MPU6050_read(I2C_HandleTypeDef *hi2c,MPU6050_Data *data)
{
	unsigned char buffer[14];
	unsigned char reg=0x3B;//加速度起�?�位寄存器地址
	
	HAL_I2C_Master_Transmit(hi2c,MPU6050_ADDR,&reg,1,HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(hi2c,MPU6050_ADDR,buffer,14,HAL_MAX_DELAY);
	
  data->Accel_X = (buffer[0] << 8) | buffer[1];
  data->Accel_Y = (buffer[2] << 8) | buffer[3];
  data->Accel_Z = (buffer[4] << 8) | buffer[5];
  data->Temp    = (buffer[6] << 8) | buffer[7];
  data->Gyro_X  = (buffer[8] << 8) | buffer[9];
  data->Gyro_Y  = (buffer[10] << 8) | buffer[11];
  data->Gyro_Z  = (buffer[12] << 8) | buffer[13];
}
//加速度等于原�?�值除以灵敏度
//原�?�数�?的标度转换和校准
void MPU6050_data_change(MPU6050_Data *data,MPU6050_Change_Data *change)
{
	float accel_scale = 4096.0; // ±8g 范围时的灵敏�?
	change->Accel_X=(float)data->Accel_X / accel_scale; //g
	change->Accel_Y=(float)data->Accel_Y / accel_scale; //g
	change->Accel_Z=(float)data->Accel_Z / accel_scale-0.25; //g
	
	float gyro_scale = 16.4; // ±2000°/s 范围时的灵敏�?
	change->Gyro_X=(float)data->Gyro_X/ gyro_scale+2.10;// 单位：�?/s
	change->Gyro_Y=(float)data->Gyro_Y/ gyro_scale-1.65;// 单位：�?/s
	change->Gyro_Z=(float)data->Gyro_Z/ gyro_scale-0.16;// 单位：�?/s
	
	change->Temp=(float)data->Temp / 340.0 + 36.53; // 单位：°C
}


//=======================================解算==========================================
float ax,ay,az;
float gx,gy,gz;
float dt = 0.01; // 采样时间间隔（�?�）
float alpha = 0.98; // 互补滤波系数

void Calculat_Read(MPU6050_Change_Data *change)
{
	ax=change->Accel_X;
	ay=change->Accel_Y;
	az=change->Accel_Z;
	gx=change->Gyro_X;
	gy=change->Gyro_Y;
	gz=change->Gyro_Z;

   // 加速度计估计的 Roll �? Pitch
    float acc_roll = 0.0, acc_pitch = 0.0;
    if (fabs(az) > 0.001) { // 避免分母�? 0
        acc_roll = atan2(ay, az) * 180.0 / M_PI;
        acc_pitch = atan2(-ax, sqrt(ay * ay + az * az)) * 180.0 / M_PI;
    }
    
    // 互补滤波器更�? Roll �? Pitch
    roll = alpha * (roll + gx * dt) + (1 - alpha) * acc_roll;
    pitch = alpha * (pitch + gy * dt) + (1 - alpha) * acc_pitch;
    
    // 陀螺仪�?分�?�算 Yaw
    yaw += gz * dt;
		
}
