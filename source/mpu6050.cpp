#include<stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"

#define I2C_PORT i2c0

#define MPU6050_ADDRESS 0x68

void mpu6050_reset();
void mpu6050_read(int16_t accelerometer[3]);


void mpu6050_reset()
{
    uint8_t reg[] = {0x6B,0x00};
    i2c_write_blocking(I2C_PORT,MPU6050_ADDRESS,reg,sizeof(reg),false);
}
void mpu6050_read(int16_t accelerometer[3])
{
    uint8_t buffer[6];
    uint8_t reg = 0x3B;
    i2c_write_blocking(I2C_PORT,MPU6050_ADDRESS,&reg,sizeof(reg),true);
    i2c_read_blocking(I2C_PORT,MPU6050_ADDRESS,buffer,sizeof(buffer),false);

 for (int i = 0; i < 3; i++) {
        accelerometer[i] = (buffer[i * 2] << 8 | buffer[(i * 2) + 1]);
    }

}