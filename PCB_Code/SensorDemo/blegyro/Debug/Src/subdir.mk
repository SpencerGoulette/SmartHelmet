################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/app_x-cube-ble1.c \
../Src/custom_bus.c \
../Src/hci_tl_interface.c \
../Src/lsm6dsl.c \
../Src/main.c \
../Src/sensor_service.c \
../Src/stm32l0xx_hal_exti.c \
../Src/stm32l0xx_hal_msp.c \
../Src/stm32l0xx_it.c \
../Src/syscalls.c \
../Src/system_stm32l0xx.c 

OBJS += \
./Src/app_x-cube-ble1.o \
./Src/custom_bus.o \
./Src/hci_tl_interface.o \
./Src/lsm6dsl.o \
./Src/main.o \
./Src/sensor_service.o \
./Src/stm32l0xx_hal_exti.o \
./Src/stm32l0xx_hal_msp.o \
./Src/stm32l0xx_it.o \
./Src/syscalls.o \
./Src/system_stm32l0xx.o 

C_DEPS += \
./Src/app_x-cube-ble1.d \
./Src/custom_bus.d \
./Src/hci_tl_interface.d \
./Src/lsm6dsl.d \
./Src/main.d \
./Src/sensor_service.d \
./Src/stm32l0xx_hal_exti.d \
./Src/stm32l0xx_hal_msp.d \
./Src/stm32l0xx_it.d \
./Src/syscalls.d \
./Src/system_stm32l0xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32L053xx -I"C:/Users/Steven/Documents/seniorproject/blegyro/Inc" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Drivers/BSP/CUSTOM" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Drivers/STM32L0xx_HAL_Driver/Inc" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Drivers/STM32L0xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Drivers/CMSIS/Device/ST/STM32L0xx/Include" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Drivers/CMSIS/Include" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Middlewares/ST/BlueNRG-MS/includes" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Middlewares/ST/BlueNRG-MS/hci/hci_tl_patterns/Basic" -I"C:/Users/Steven/Documents/seniorproject/blegyro/Middlewares/ST/BlueNRG-MS/utils"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


