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
static void MX_USART1_UART_Init(void);

static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}
int32_t GYRO_INIT(SPI_HandleTypeDef hspi1)
{
	MX_USART1_UART_Init();

	//gren LED init
	int32_t ret = 0;
	uint8_t datain;
	uint8_t *dataout = 0 ;
	GPIO_InitTypeDef GPIO_InitStruct;
//	HAL_SPI_Transmit(&hspi1, LSM6DS3_ACC_GYRO_WHO_AM_I_REG, 1, 0x1000U);

	uint8_t regg = 0x8F ;

	uint8_t readCheck = 0;

	//Check the ID register to determine if the operation was a success.
	//6A is device ID
	read_reg(hspi1, regg, &readCheck,1,huart1);
	if( readCheck != 0x6A )
	{
		return 6;
		  HAL_GPIO_WritePin(GPIOA ,GPIO_PIN_5, GPIO_PIN_SET);
		//(void)snprintf(dataOut, 50, "reg: %8ld\r\n",readCheck);
		// HAL_GPIO_WritePin(GPIOA ,GPIO_PIN_5, GPIO_PIN_SET);
		  //HAL_UART_Transmit(&huart1, dataOut, sizeof(dataOut),50);
		//ret = 5;
	}

	if(lsm6dsl_acc_set_data_rate(hspi1) != 0)
	{
		//error setting data rate
		return 1;
	}
	if(lsm6dsl_acc_set_fullscale(hspi1) != 0)
	{
		//error setting data rate
		return 2;
	}
	if(lsm6dsl_gyro_set_data_rate(hspi1) != 0)
	{
		//error setting data rate
		return 3;
	}
	if(lsm6dsl_gyro_set_fullscale(hspi1) != 0)
	{
		//error setting data rate
		return 4;
	}

}

int32_t lsm6dsl_acc_set_data_rate(SPI_HandleTypeDef hspi1  )
{
  uint8_t ctrl1_xl;
  int32_t ret = 0;

  //ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
  ret = read_reg(hspi1,  LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1,huart1);

  if(ret == 0){
	//ctrl1_xl = (uint8_t) val;
   // ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
    ret = write_reg(hspi1,  LSM6DSL_CTRL1_XL, (uint8_t*)LSM6DSL_XL_ODR_416Hz, 1,huart1);

  }
  return ret;
}
int32_t lsm6dsl_acc_set_fullscale(SPI_HandleTypeDef hspi1  )
{
  uint8_t ctrl1_xl;
  int32_t ret = 0;

  //ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
  ret = read_reg(hspi1,  LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1,huart1);

  if(ret == 0){
	//ctrl1_xl = (uint8_t) val;
   // ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
    ret = write_reg(hspi1,  LSM6DSL_CTRL1_XL, (uint8_t*)LSM6DSL_16g, 1,huart1);

  }
  return ret;
}
int32_t lsm6dsl_gyro_set_data_rate(SPI_HandleTypeDef hspi1  )
{
  uint8_t ctrl1_xl;
  int32_t ret = 0;

  //ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
  ret = read_reg(hspi1,  LSM6DSL_CTRL2_G, (uint8_t*)&ctrl1_xl, 1,huart1);

  if(ret == 0){
	//ctrl1_xl = (uint8_t) val;
   // ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
    ret = write_reg(hspi1,  LSM6DSL_CTRL2_G, (uint8_t*)LSM6DSL_XL_ODR_416Hz, 1,huart1);

  }
  return ret;
}
int32_t lsm6dsl_gyro_set_fullscale(SPI_HandleTypeDef hspi1  )
{
  uint8_t ctrl1_xl;
  int32_t ret = 0;

  //ret = lsm6dsl_read_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
  ret = read_reg(hspi1,  LSM6DSL_CTRL2_G, (uint8_t*)&ctrl1_xl, 1,huart1);

  if(ret == 0){
	//ctrl1_xl = (uint8_t) val;
   // ret = lsm6dsl_write_reg(ctx, LSM6DSL_CTRL1_XL, (uint8_t*)&ctrl1_xl, 1);
    ret = write_reg(hspi1,  LSM6DSL_CTRL2_G, (uint8_t*)LSM6DSL_2000dps, 1,huart1);

  }
  return ret;
}
float readFloatGyroX( SPI_HandleTypeDef hspi1  )
{
	float output = calcGyro(lsm6dsl_gyro_get_raw_x(hspi1));

	return output;
}
float readFloatGyroY( SPI_HandleTypeDef hspi1  )
{
	float output = calcGyro(lsm6dsl_gyro_get_raw_y(hspi1));
	return output;
}
int16_t readFloatGyroZ( SPI_HandleTypeDef hspi1  )
{
	//float output = calcGyro(lsm6dsl_gyro_get_raw_z(hspi1));
	int16_t output = lsm6dsl_gyro_get_raw_z(hspi1);

	return output;
}

float calcGyro( int16_t input )
{
	//set eariler to 250
	uint8_t gyroRangeDivisor = 250 / 125;
	if ( 250 == 250 ) {
		//gyroRangeDivisor = 2;
	}

	float output = (float)input * 4.375 * (gyroRangeDivisor) / 1000;
	return output;
}
float readFloatAccelX(SPI_HandleTypeDef hspi1 )
{
	float output = calcAccel(lsm6dsl_acc_get_raw_x(hspi1));
	return output;
}
float readFloatAccelY(SPI_HandleTypeDef hspi1 )
{
	float output = calcAccel(lsm6dsl_acc_get_raw_y(hspi1));
	return output;
}
float readFloatAccelZ(SPI_HandleTypeDef hspi1 )
{
	float output = calcAccel(lsm6dsl_acc_get_raw_z(hspi1));
	return output;
}
float calcAccel( int16_t input )
{
	//16 max G force
	float output = (float)input * 0.061 * (2 >> 1) / 1000;
	return output;
}
int16_t lsm6dsl_acc_get_raw_x(SPI_HandleTypeDef hspi1  )
{
	int16_t data = 0;
	readRegisterInt16(hspi1, &data, LSM6DS3_ACC_GYRO_OUTX_L_XL);
//	(void)snprintf(dataOut, 50, "X: %ld\r\n ", data);
	//(void)snprintf(dataOut, 50, "Xasd\r\n ");

	// HAL_GPIO_WritePin(GPIOA ,GPIO_PIN_5, GPIO_PIN_SET);
		//  HAL_UART_Transmit(&huart1, &data, 2,50);
	return data;
}
int16_t lsm6dsl_acc_get_raw_y(SPI_HandleTypeDef hspi1  )
{
	int16_t data = 0;
	readRegisterInt16(hspi1, &data, LSM6DS3_ACC_GYRO_OUTY_L_XL);
	return data;
}
int16_t lsm6dsl_acc_get_raw_z(SPI_HandleTypeDef hspi1  )
{
	int16_t data = 0;
	readRegisterInt16(hspi1, &data, LSM6DS3_ACC_GYRO_OUTZ_L_XL);
	return data;
}
int16_t lsm6dsl_gyro_get_raw_x(SPI_HandleTypeDef hspi1  )
{
	int16_t data  = 5;
	readRegisterInt16(hspi1, &data, LSM6DS3_ACC_GYRO_OUTX_L_XL);
	return data;
}
int16_t lsm6dsl_gyro_get_raw_y(SPI_HandleTypeDef hspi1  )
{
	int16_t data = 0;
	readRegisterInt16(hspi1, &data, LSM6DS3_ACC_GYRO_OUTY_L_G);
	return data;
}
int16_t lsm6dsl_gyro_get_raw_z(SPI_HandleTypeDef hspi1  )
{
	int16_t data = 0;
	readRegisterInt16(hspi1, &data, LSM6DS3_ACC_GYRO_OUTZ_L_G);
	return data;
}
int32_t readRegisterInt16( SPI_HandleTypeDef hspi1, int16_t* dataout, uint8_t reg  )
{
	uint8_t buff[2];
	int32_t ret;
	int16_t output;
	ret = read_reg(hspi1, reg, &buff,2,huart1);
	output = (int16_t)buff[0] | (int16_t)(buff[1] << 8);

	*dataout = output;

	return ret;
}
int32_t read_reg(SPI_HandleTypeDef hspi1 , uint16_t datareg, uint8_t * buff,  uint16_t len,UART_HandleTypeDef huart1)
{
	  int32_t ret = 0;
	  uint8_t dataReg = (uint8_t)datareg;

	  /* CS Enable */
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
		//  HAL_Delay(25);

	  if (SPI1_Send(hspi1, &dataReg, 1) > 0)
	  {
	    ret = 5;
	  }

	  if (SPI1_Recv(hspi1, buff, len,huart1) > 0)
	  {
	    ret = 5;
	  }

	  /* CS Disable */
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

	  return ret;

}
int32_t write_reg(SPI_HandleTypeDef hspi1 , uint16_t datareg, uint8_t * buff,  uint16_t len,UART_HandleTypeDef huart1)
{
	  int32_t ret = 0;
	  uint8_t dataReg = (uint8_t)datareg;

	  /* CS Enable */
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
	  if (SPI1_Send(hspi1, &dataReg, 1) > 0)
	  {
	    ret = 5;
	  }

	  if (SPI1_Send(hspi1, &buff, len) > 0)
	  {
	    ret = 5;
	  }

	  /* CS Disable */
	  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

	  return ret;
}
int32_t SPI1_Send(SPI_HandleTypeDef hspi1, uint8_t *pData, uint16_t Length)
{
  int32_t ret = 0;

  if(HAL_SPI_Transmit(&hspi1, pData, Length, 0x1000U) != HAL_OK)
  {
      ret = 5;
  }
  return ret;
}
int32_t  SPI1_Recv(SPI_HandleTypeDef hspi1, uint8_t *pData, uint16_t Length,UART_HandleTypeDef huart1)
{
  int32_t ret = 0;

  if(HAL_SPI_Receive(&hspi1, pData, Length, 0x1000U) != HAL_OK)
  {
	// HAL_GPIO_WritePin(GPIOA ,GPIO_PIN_5, GPIO_PIN_SET);

		//(void)snprintf(dataOut, 50, "reg1: %ld\r\n",pData);
      ret = 5;
  }

  return ret;
}
