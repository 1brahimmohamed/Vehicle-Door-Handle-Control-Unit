################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Gpio/Gpio.c 

OBJS += \
./Gpio/Gpio.o 

C_DEPS += \
./Gpio/Gpio.d 


# Each subdirectory must supply rules for building sources it contributes
Gpio/%.o: ../Gpio/%.c Gpio/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F401xE -DHSE_VALUE=8000000 -I"../include" -I"D:\My PC\Projects\Embedded\Valeo\Final Project\DoorHandle\Gpt" -I"D:\My PC\Projects\Embedded\Valeo\Final Project\DoorHandle\Gpio" -I"D:\My PC\Projects\Embedded\Valeo\Final Project\DoorHandle\Lib" -I"D:\My PC\Projects\Embedded\Valeo\Final Project\DoorHandle\Rcc" -I"../system/include" -I"../system/include/cmsis" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


