/*
 * lsm6dsl.h
 *
 *  Created on: Oct 24, 2019
 *      Author: Steven
 */
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_spi.h"
#ifndef LSM6DSL_H_
#define LSM6DSL_H_



#define LSM6DSL_ACC_GYRO_TEST_PAGE  			0X00
#define LSM6DSL_ACC_GYRO_RAM_ACCESS  			0X01
#define LSM6DSL_ACC_GYRO_SENSOR_SYNC_TIME  		0X04
#define LSM6DSL_ACC_GYRO_SENSOR_SYNC_EN  		0X05
#define LSM6DSL_ACC_GYRO_FIFO_CTRL1  			0X06
#define LSM6DSL_ACC_GYRO_FIFO_CTRL2  			0X07
#define LSM6DSL_ACC_GYRO_FIFO_CTRL3  			0X08
#define LSM6DSL_ACC_GYRO_FIFO_CTRL4  			0X09
#define LSM6DSL_ACC_GYRO_FIFO_CTRL5  			0X0A
#define LSM6DSL_ACC_GYRO_ORIENT_CFG_G  			0X0B
#define LSM6DSL_ACC_GYRO_REFERENCE_G  			0X0C
#define LSM6DSL_ACC_GYRO_INT1_CTRL  			0X0D
#define LSM6DSL_ACC_GYRO_INT2_CTRL  			0X0E
#define LSM6DSL_ACC_GYRO_WHO_AM_I_REG  			0X0F
#define LSM6DSL_ACC_GYRO_CTRL1_XL  			0X10
#define LSM6DSL_ACC_GYRO_CTRL2_G  			0X11
#define LSM6DSL_ACC_GYRO_CTRL3_C  			0X12
#define LSM6DSL_ACC_GYRO_CTRL4_C  			0X13
#define LSM6DSL_ACC_GYRO_CTRL5_C  			0X14
#define LSM6DSL_ACC_GYRO_CTRL6_G  			0X15
#define LSM6DSL_ACC_GYRO_CTRL7_G  			0X16
#define LSM6DSL_ACC_GYRO_CTRL8_XL  			0X17
#define LSM6DSL_ACC_GYRO_CTRL9_XL  			0X18
#define LSM6DSL_ACC_GYRO_CTRL10_C  			0X19
#define LSM6DSL_ACC_GYRO_MASTER_CONFIG  		0X1A
#define LSM6DSL_ACC_GYRO_WAKE_UP_SRC  			0X1B
#define LSM6DSL_ACC_GYRO_TAP_SRC  			0X1C
#define LSM6DSL_ACC_GYRO_D6D_SRC  			0X1D
#define LSM6DSL_ACC_GYRO_STATUS_REG  			0X1E
#define LSM6DSL_ACC_GYRO_OUT_TEMP_L  			0X20
#define LSM6DSL_ACC_GYRO_OUT_TEMP_H  			0X21
#define LSM6DSL_ACC_GYRO_OUTX_L_G  			0X22
#define LSM6DSL_ACC_GYRO_OUTX_H_G  			0X23
#define LSM6DSL_ACC_GYRO_OUTY_L_G  			0X24
#define LSM6DSL_ACC_GYRO_OUTY_H_G  			0X25
#define LSM6DSL_ACC_GYRO_OUTZ_L_G  			0X26
#define LSM6DSL_ACC_GYRO_OUTZ_H_G  			0X27
#define LSM6DSL_ACC_GYRO_OUTX_L_XL  			0X28
#define LSM6DSL_ACC_GYRO_OUTX_H_XL  			0X29
#define LSM6DSL_ACC_GYRO_OUTY_L_XL  			0X2A
#define LSM6DSL_ACC_GYRO_OUTY_H_XL  			0X2B
#define LSM6DSL_ACC_GYRO_OUTZ_L_XL  			0X2C
#define LSM6DSL_ACC_GYRO_OUTZ_H_XL  			0X2D
#define LSM6DSL_ACC_GYRO_SENSORHUB1_REG  		0X2E
#define LSM6DSL_ACC_GYRO_SENSORHUB2_REG  		0X2F
#define LSM6DSL_ACC_GYRO_SENSORHUB3_REG  		0X30
#define LSM6DSL_ACC_GYRO_SENSORHUB4_REG  		0X31
#define LSM6DSL_ACC_GYRO_SENSORHUB5_REG  		0X32
#define LSM6DSL_ACC_GYRO_SENSORHUB6_REG  		0X33
#define LSM6DSL_ACC_GYRO_SENSORHUB7_REG  		0X34
#define LSM6DSL_ACC_GYRO_SENSORHUB8_REG  		0X35
#define LSM6DSL_ACC_GYRO_SENSORHUB9_REG  		0X36
#define LSM6DSL_ACC_GYRO_SENSORHUB10_REG  		0X37
#define LSM6DSL_ACC_GYRO_SENSORHUB11_REG  		0X38
#define LSM6DSL_ACC_GYRO_SENSORHUB12_REG  		0X39
#define LSM6DSL_ACC_GYRO_FIFO_STATUS1  			0X3A
#define LSM6DSL_ACC_GYRO_FIFO_STATUS2  			0X3B
#define LSM6DSL_ACC_GYRO_FIFO_STATUS3  			0X3C
#define LSM6DSL_ACC_GYRO_FIFO_STATUS4  			0X3D
#define LSM6DSL_ACC_GYRO_FIFO_DATA_OUT_L  		0X3E
#define LSM6DSL_ACC_GYRO_FIFO_DATA_OUT_H  		0X3F
#define LSM6DSL_ACC_GYRO_TIMESTAMP0_REG  		0X40
#define LSM6DSL_ACC_GYRO_TIMESTAMP1_REG  		0X41
#define LSM6DSL_ACC_GYRO_TIMESTAMP2_REG  		0X42
#define LSM6DSL_ACC_GYRO_STEP_COUNTER_L  		0X4B
#define LSM6DSL_ACC_GYRO_STEP_COUNTER_H  		0X4C
#define LSM6DSL_ACC_GYRO_FUNC_SRC  			0X53
#define LSM6DSL_ACC_GYRO_TAP_CFG1  			0X58
#define LSM6DSL_ACC_GYRO_TAP_THS_6D  			0X59
#define LSM6DSL_ACC_GYRO_INT_DUR2  			0X5A
#define LSM6DSL_ACC_GYRO_WAKE_UP_THS  			0X5B
#define LSM6DSL_ACC_GYRO_WAKE_UP_DUR  			0X5C
#define LSM6DSL_ACC_GYRO_FREE_FALL  			0X5D
#define LSM6DSL_ACC_GYRO_MD1_CFG  			0X5E
#define LSM6DSL_ACC_GYRO_MD2_CFG  			0X5F
#define LSM6DSL_XL_ODR_416Hz				0x06
#define LSM6DSL_CTRL1_XL                     0x10U
#define LSM6DSL_2g       0
#define LSM6DSL_16g      1
#define LSM6DSL_4g       2
#define LSM6DSL_8g       3
#define  LSM6DSL_250dps      0
#define  LSM6DSL_125dps      1
#define  LSM6DSL_500dps      2
#define  LSM6DSL_1000dps     4
#define  LSM6DSL_2000dps     6
#define  LSM6DSL_GY_FS_ND    7
#define  LSM6DSL_GY_ODR_OFF      0
#define  LSM6DSL_GY_ODR_12Hz5    1
#define  LSM6DSL_GY_ODR_26Hz     2
#define  LSM6DSL_GY_ODR_52Hz     3
#define  LSM6DSL_GY_ODR_104Hz    4
#define  LSM6DSL_GY_ODR_208Hz    5
#define  LSM6DSL_GY_ODR_416Hz    6
#define  LSM6DSL_GY_ODR_833Hz    7
#define  LSM6DSL_GY_ODR_1k66Hz   8
#define  LSM6DSL_GY_ODR_3k33Hz   9
#define  LSM6DSL_GY_ODR_6k66Hz  10
#define  LSM6DSL_GY_ODR_ND      11
#define LSM6DSL_CTRL2_G                      0x11U
#define LSM6DSL_ACC_GYRO_BW_XL_400Hz 		  0x00
#define LSM6DSL_ACC_GYRO_BW_XL_200Hz 		  0x01
#define LSM6DSL_ACC_GYRO_BW_XL_100Hz 		  0x02
#define LSM6DSL_ACC_GYRO_BW_XL_50Hz 		  0x03
#define LSM6DSL_ACC_GYRO_FS_XL_2g 		  0x00
#define LSM6DSL_ACC_GYRO_FS_XL_16g 		  0x04
#define LSM6DSL_ACC_GYRO_FS_XL_4g 		  0x08
#define LSM6DSL_ACC_GYRO_FS_XL_8g 		  0x0C
#define LSM6DSL_ACC_GYRO_ODR_XL_13Hz 		          0x10
#define LSM6DSL_ACC_GYRO_ODR_XL_26Hz 		          0x20
#define LSM6DSL_ACC_GYRO_ODR_XL_52Hz 		          0x30
#define LSM6DSL_ACC_GYRO_ODR_XL_104Hz 		  0x40
#define LSM6DSL_ACC_GYRO_ODR_XL_208Hz 		  0x50
#define LSM6DSL_ACC_GYRO_ODR_XL_416Hz 		  0x60
#define LSM6DSL_ACC_GYRO_ODR_XL_833Hz 		  0x70
#define LSM6DSL_ACC_GYRO_ODR_XL_1660Hz 		  0x80
#define LSM6DSL_ACC_GYRO_ODR_XL_3330Hz 		  0x90
#define LSM6DSL_ACC_GYRO_ODR_XL_6660Hz 		  0xA0
#define LSM6DSL_ACC_GYRO_ODR_XL_13330Hz 		  0xB0
#define LSM6DSL_ACC_GYRO_FS_G_245dps 		  0x00
#define LSM6DSL_ACC_GYRO_FS_G_500dps 		  0x04
#define LSM6DSL_ACC_GYRO_FS_G_1000dps 		  0x08
#define LSM6DSL_ACC_GYRO_FS_G_2000dps 		  0x0C
#define LSM6DSL_ACC_GYRO_ODR_G_13Hz 		  0x10
#define LSM6DSL_ACC_GYRO_ODR_G_26Hz 		  0x20
#define LSM6DSL_ACC_GYRO_ODR_G_52Hz 		  0x30
#define LSM6DSL_ACC_GYRO_ODR_G_104Hz 		  0x40
#define LSM6DSL_ACC_GYRO_ODR_G_208Hz 		  0x50
#define LSM6DSL_ACC_GYRO_ODR_G_416Hz 		  0x60
#define LSM6DSL_ACC_GYRO_ODR_G_833Hz 		  0x70
#define LSM6DSL_ACC_GYRO_ODR_G_1660Hz 		  0x80

int32_t GYRO_INIT(SPI_HandleTypeDef hspi1);
int32_t lsm6dsl_acc_set_data_rate(SPI_HandleTypeDef hspi1 );
int32_t lsm6dsl_acc_set_fullscale(SPI_HandleTypeDef hspi1 );
int32_t lsm6dsl_gyro_set_data_rate(SPI_HandleTypeDef hspi1 );
int32_t lsm6dsl_gyro_set_fullscale(SPI_HandleTypeDef hspi1 );
int16_t readRegisterInt16( SPI_HandleTypeDef hspi1, int16_t* dataout, uint8_t reg );
int16_t lsm6dsl_acc_get_raw_x(SPI_HandleTypeDef hspi1 );
int16_t lsm6dsl_acc_get_raw_y(SPI_HandleTypeDef hspi1 );
int16_t lsm6dsl_acc_get_raw_z(SPI_HandleTypeDef hspi1 );
int16_t lsm6dsl_gyro_get_raw_x(SPI_HandleTypeDef hspi1 );
int16_t lsm6dsl_gyro_get_raw_y(SPI_HandleTypeDef hspi1 );
int16_t lsm6dsl_gyro_get_raw_z(SPI_HandleTypeDef hspi1 );
float readFloatAccelX(SPI_HandleTypeDef hspi1);
float readFloatAccelY(SPI_HandleTypeDef hspi1);
float readFloatAccelZ(SPI_HandleTypeDef hspi1);
float calcAccel( int16_t input );
float readFloatGyroX( SPI_HandleTypeDef hspi1 );
float readFloatGyroY( SPI_HandleTypeDef hspi1 );
float readFloatGyroZ( SPI_HandleTypeDef hspi1 );
float calcGyro( int16_t input );



int32_t read_reg(SPI_HandleTypeDef hspi1 , uint16_t datareg, uint8_t * buff,  uint16_t len);
int32_t write_reg(SPI_HandleTypeDef hspi1 , uint16_t datareg, uint8_t * buff,  uint16_t len);
int32_t SPI1_Send(SPI_HandleTypeDef hspi1, uint8_t *pData, uint16_t Length);
int32_t  SPI1_Recv(SPI_HandleTypeDef hspi1, uint8_t *pData, uint16_t Length);

#endif /* LSM6DSL_H_ */
