################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/en.X-CUBE-BLE1/STM32CubeExpansion_BLE1_V4.4.0/Middlewares/ST/BlueNRG-MS/utils/ble_list.c 

OBJS += \
./Middlewares/BlueNRG-MS/Wireless/Utils/ble_list.o 

C_DEPS += \
./Middlewares/BlueNRG-MS/Wireless/Utils/ble_list.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/BlueNRG-MS/Wireless/Utils/ble_list.o: D:/en.X-CUBE-BLE1/STM32CubeExpansion_BLE1_V4.4.0/Middlewares/ST/BlueNRG-MS/utils/ble_list.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L053xx -I"D:/en.X-CUBE-BLE1/STM32CubeExpansion_BLE1_V4.4.0/Projects/STM32L053R8-Nucleo/Applications/SensorDemo/Inc" -I"D:/en.X-CUBE-BLE1/STM32CubeExpansion_BLE1_V4.4.0/Drivers/STM32L0xx_HAL_Driver/Inc" -I"D:/en.X-CUBE-BLE1/STM32CubeExpansion_BLE1_V4.4.0/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"D:/en.X-CUBE-BLE1/STM32CubeExpansion_BLE1_V4.4.0/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"D:/en.X-CUBE-BLE1/STM32CubeExpansion_BLE1_V4.4.0/Drivers/CMSIS/Include" -I"D:/en.X-CUBE-BLE1/STM32CubeExpansion_BLE1_V4.4.0/Middlewares/ST/BlueNRG-MS/includes" -I"D:/en.X-CUBE-BLE1/STM32CubeExpansion_BLE1_V4.4.0/Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic" -I"D:/en.X-CUBE-BLE1/STM32CubeExpansion_BLE1_V4.4.0/Middlewares/ST/BlueNRG-MS/utils"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


