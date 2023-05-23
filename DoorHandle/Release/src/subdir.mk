################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/helpers.c \
../src/main.c 

OBJS += \
./src/helpers.o \
./src/main.o 

C_DEPS += \
./src/helpers.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c src/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F401xE -DHSE_VALUE=8000000 -I"../include" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\Gpt" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\Gpio" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\Lib" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\Rcc" -I"../system/include" -I"../system/include/cmsis" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


