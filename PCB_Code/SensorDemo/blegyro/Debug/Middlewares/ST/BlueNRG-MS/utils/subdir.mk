################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/ST/BlueNRG-MS/utils/ble_list.c 

OBJS += \
./Middlewares/ST/BlueNRG-MS/utils/ble_list.o 

C_DEPS += \
./Middlewares/ST/BlueNRG-MS/utils/ble_list.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/ST/BlueNRG-MS/utils/%.o: ../Middlewares/ST/BlueNRG-MS/utils/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L053xx -I"C:/Users/Steven/Documents/seniorproject/blegyro/Inc" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Drivers/BSP/CUSTOM" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Drivers/CMSIS/Include" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Middlewares/ST/BlueNRG-MS/includes" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Middlewares/ST/BlueNRG-MS/utils"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


