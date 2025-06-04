################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/BlueNRG-MS/Wireless/Utils/subdir.mk
-include Middlewares/BlueNRG-MS/Wireless/HCI_TL/Basic/subdir.mk
-include Middlewares/BlueNRG-MS/Wireless/Controller/subdir.mk
-include Drivers/STM32L0xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Application/User/subdir.mk
-include Application/SW4STM32/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: SensorDemo.elf

# Tool invocations
SensorDemo.elf: $(OBJS) $(USER_OBJS) ../STM32L053R8Tx_FLASH.ld
	@echo 'Building target: $@'
	@echo 'Invoking: MCU GCC Linker'
	arm-none-eabi-gcc -mcpu=cortex-m0plus -mthumb -mfloat-abi=soft -specs=nosys.specs -specs=nano.specs  -u _printf_float -T"../STM32L053R8Tx_FLASH.ld" -Wl,-Map=output.map -Wl,--gc-sections -o "SensorDemo.elf" @"objects.list" $(USER_OBJS) $(LIBS) -lm
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

post-build:
	-@echo 'Generating hex and Printing size information:'
	arm-none-eabi-objcopy -O ihex "SensorDemo.elf" "SensorDemo.hex"
	arm-none-eabi-size "SensorDemo.elf"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
