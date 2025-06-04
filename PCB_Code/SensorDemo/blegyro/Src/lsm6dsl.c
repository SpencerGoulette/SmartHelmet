/*

 * lsm6dsl.c
 *
 *  Created on: Oct 24, 2019
 *      Author: Steven
 */
#include "lsm6dsl.h"
#include "stm32l0xx_hal.h"
#include "stm32l0xx_hal_spi.h"

static char dataOut[50];


int32_t GYRO_INIT(SPI_HandleTypeDef hspi1)
{

	int32_t ret = 0;
	uint8_t datain;
	uint8_t *dataout = 0 ;

	uint8_t regg = 0x8F ;

	uint8_t readCheck = 0;

	//Check the ID register to determine if the operation was a success.
	//6A is device ID
	read_reg(hspi1, regg, &readCheck,1);
	if( readCheck != 0x6A )
	{
		HAL_GPIO_WritePin(GPIOA ,GPIO_PIN_10, GPIO_PIN_SET);

		return 6;

	}
	//up the accelometer
	if(lsm6dsl_acc_set_data_rate(hspi1) != 0)
	{
		HAL_GPIO_WritePin(GPIOA ,GPIO_PIN_10, GPIO_PIN_SET);

		//error setting data rate
		return 1;
	}
	//set up gyroscope
	if(lsm6dsl_gyro_set_data_rate(hspi1) != 0)
	{
		HAL_GPIO_WritePin(GPIOA ,GPIO_PIN_10, GPIO_PIN_SET);

		//error setting data rate
		return 3;
	}

	//no error setting sensor up
	return 0;

}

int32_t lsm6dsl_acc_set_data_rate(SPI_HandleTypeDef hspi1  )
{
  uint8_t ctrl1_xl;
  int32_t ret = 0;
  //
  //+30x02 |0x04|0x60
  //ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
//  ret = read_reg(hspi1,  LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1,huart1);

  if(ret == 0){

    ret = write_reg(hspi1,  LSM6DSL_ACC_GYRO_CTRL1_XL, ( LSM6DSL_ACC_GYRO_BW_XL_100Hz |LSM6DSL_ACC_GYRO_FS_XL_16g|LSM6DSL_ACC_GYRO_ODR_XL_416Hz), 1);

  }
  return ret;
}
int32_t lsm6dsl_acc_set_fullscale(SPI_HandleTypeDef hspi1  )
{
  uint8_t ctrl1_xl;
  int32_t ret = 0;

  //ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
  ret = read_reg(hspi1,  LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);

  if(ret == 0){
	//ctrl1_xl = (uint8_t) val;
   // ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
    ret = write_reg(hspi1,  LSM6DSL_CTRL1_XL, (uint8_t*)LSM6DSL_2g, 1);

  }
  return ret;
}
int32_t lsm6dsl_gyro_set_data_rate(SPI_HandleTypeDef hspi1  )
{
  uint8_t ctrl1_xl;
  int32_t ret = 0;

  //ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
  ret = read_reg(hspi1,  LSM6DSL_CTRL2_G, (uint8_t*)&ctrl1_xl, 1);

  if(ret == 0){
	//ctrl1_xl = (uint8_t) val;
   // ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
    ret = write_reg(hspi1,  LSM6DSL_CTRL2_G, (LSM6DSL_ACC_GYRO_FS_G_2000dps | LSM6DSL_ACC_GYRO_ODR_G_416Hz), 1);

  }
  return ret;
}
int32_t lsm6dsl_gyro_set_fullscale(SPI_HandleTypeDef hspi1  )
{
  uint8_t ctrl1_xl;
  int32_t ret = 0;

  //ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
  ret = read_reg(hspi1,  LSM6DSL_CTRL2_G, (uint8_t*)&ctrl1_xl, 1);

  if(ret == 0){
	//ctrl1_xl = (uint8_t) val;
   // ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
    ret = write_reg(hspi1,  LSM6DSL_CTRL2_G, (uint8_t*)LSM6DSL_250dps, 1);

  }
  return ret;
}
float readFloatGyroX( SPI_HandleTypeDef hspi1  )
{
	//get raw values than get actual value than return it
	float output = calcGyro(lsm6dsl_gyro_get_raw_x(hspi1));

	return output;
}
float readFloatGyroY( SPI_HandleTypeDef hspi1  )
{
	//get raw values than get actual value than return it

	float output = calcGyro(lsm6dsl_gyro_get_raw_y(hspi1));
	return output;
}
float readFloatGyroZ( SPI_HandleTypeDef hspi1  )
{
	//get raw values than get actual value than return it

	float output = calcGyro(lsm6dsl_gyro_get_raw_z(hspi1));
	//int16_t output = lsm6dsl_gyro_get_raw_z(hspi1);

	return output;
}

float calcGyro( int16_t input )
{
	//set eariler to 250
	//calculate actual value for gyro
	uint8_t gyroRangeDivisor = 2000 / 125;
	if ( 250 == 250 ) {
		//gyroRangeDivisor = 2;
	}


	float output = (float)input * 4.375 * (gyroRangeDivisor) / 1000;
	return output;
}
float readFloatAccelX(SPI_HandleTypeDef hspi1 )
{
	//get raw values than get actual value than return it

	float output = calcAccel(lsm6dsl_acc_get_raw_x(hspi1));
	return output;
}
float readFloatAccelY(SPI_HandleTypeDef hspi1 )
{
	//get raw values than get actual value than return it

	float output = calcAccel(lsm6dsl_acc_get_raw_y(hspi1));
	return output;
}
float readFloatAccelZ(SPI_HandleTypeDef hspi1 )
{
	//get raw values than get actual value than return it

	float output = calcAccel(lsm6dsl_acc_get_raw_z(hspi1));
	return output;
}
float calcAccel( int16_t input )
{
	//16 max G force
	float output = (float)input * 0.061 * (16 >> 1) / 1000;
	return output;
}
int16_t lsm6dsl_acc_get_raw_x(SPI_HandleTypeDef hspi1  )
{
	int16_t data = 0;
	//read register for proper axis 0x80 is telling the device you want to read that register
	readRegisterInt16(hspi1, &data,(0x80 | LSM6DSL_ACC_GYRO_OUTX_L_XL));

	return data;
}
int16_t lsm6dsl_acc_get_raw_y(SPI_HandleTypeDef hspi1  )
{
	int16_t data = 0;
	//read register for proper axis 0x80 is telling the device you want to read that register

	readRegisterInt16(hspi1, &data, (0x80 | LSM6DSL_ACC_GYRO_OUTY_L_XL));
	return data;
}
int16_t lsm6dsl_acc_get_raw_z(SPI_HandleTypeDef hspi1  )
{
	int16_t data = 0;
	//read register for proper axis 0x80 is telling the device you want to read that register

	readRegisterInt16(hspi1, &data,( 0x80 | LSM6DSL_ACC_GYRO_OUTZ_L_XL));
	return data;
}
int16_t lsm6dsl_gyro_get_raw_x(SPI_HandleTypeDef hspi1  )
{
	int16_t data = 10;
	//read register for proper axis 0x80 is telling the device you want to read that register

	readRegisterInt16(hspi1, &data,( 0x80 | LSM6DSL_ACC_GYRO_OUTX_L_G));
	return data;
}
int16_t lsm6dsl_gyro_get_raw_y(SPI_HandleTypeDef hspi1  )
{
	int16_t data = 0;
	//read register for proper axis 0x80 is telling the device you want to read that register

	readRegisterInt16(hspi1, &data,( 0x80 | LSM6DSL_ACC_GYRO_OUTY_L_G));
	return data;
}
int16_t lsm6dsl_gyro_get_raw_z(SPI_HandleTypeDef hspi1  )
{
	int16_t data = 0;
	//read register for proper axis 0x80 is telling the device you want to read that register

	readRegisterInt16(hspi1, &data, ( 0x80 |LSM6DSL_ACC_GYRO_OUTZ_L_G));
	return data;
}
int16_t readRegisterInt16( SPI_HandleTypeDef hspi1, int16_t* dataout, uint8_t reg  )
{
	uint8_t buff[2];
	int16_t output;
	read_reg(hspi1, reg, &buff,2);
	output = (int16_t)buff[0] | (int16_t)(buff[1] << 8);

	*dataout = output;

	return buff;
}
int32_t read_reg(SPI_HandleTypeDef hspi1 , uint16_t datareg, uint8_t * buff,  uint16_t len)
{
	  int32_t ret = 0;
	  uint8_t dataReg = (uint8_t)datareg;

	  /* CS Enable */
	    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

		//  HAL_Delay(25);

	  if (SPI1_Send(hspi1, &dataReg, 1) > 0)
	  {
	    ret = 5;
	  }

	  if (SPI1_Recv(hspi1, buff, len) > 0)
	  {
	    ret = 5;
	  }


	  /* CS Disable */
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);

	  return ret;

}
int32_t write_reg(SPI_HandleTypeDef hspi1 , uint16_t datareg, uint8_t * buff,  uint16_t len)
{
	  int32_t ret = 0;
	  uint8_t dataReg = (uint8_t)datareg;

	  /* CS Enable */
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_RESET);

	  if (SPI1_Send(hspi1, &dataReg, 1) > 0)
	  {
	    ret = 5;
	  }

	  if (SPI1_Send(hspi1, &buff, len) > 0)
	  {
	    ret = 5;
	  }

	  /* CS Disable */
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8, GPIO_PIN_SET);

	  return ret;
}
int32_t SPI1_Send(SPI_HandleTypeDef hspi1, uint8_t *pData, uint16_t Length)
{
  int32_t ret = 0;

  if(HAL_SPI_Transmit(&hspi1, pData, Length, 0x1000U) != HAL_OK)
  {
	  //error
      ret = 5;
  }
  return ret;
}
int32_t  SPI1_Recv(SPI_HandleTypeDef hspi1, uint8_t *pData, uint16_t Length)
{
  int32_t ret = 0;

  if(HAL_SPI_Receive(&hspi1, pData, Length, 0x1000U) != HAL_OK)
  {
	  //error
      ret = 5;
  }

  return ret;
}
