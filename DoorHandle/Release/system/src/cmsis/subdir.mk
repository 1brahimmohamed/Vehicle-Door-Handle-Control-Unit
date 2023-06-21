################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../system/src/cmsis/system_stm32f4xx.c \
../system/src/cmsis/vectors_stm32f401xe.c 

OBJS += \
./system/src/cmsis/system_stm32f4xx.o \
./system/src/cmsis/vectors_stm32f401xe.o 

C_DEPS += \
./system/src/cmsis/system_stm32f4xx.d \
./system/src/cmsis/vectors_stm32f401xe.d 


# Each subdirectory must supply rules for building sources it contributes
system/src/cmsis/system_stm32f4xx.o: ../system/src/cmsis/system_stm32f4xx.c system/src/cmsis/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F401xE -DHSE_VALUE=8000000 -I"../include" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\Gpt" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\Gpio" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\Lib" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\Rcc" -I"../system/include" -I"../system/include/cmsis" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\EXTI" -std=gnu11 -Wno-padded -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

system/src/cmsis/%.o: ../system/src/cmsis/%.c system/src/cmsis/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GNU Arm Cross C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -Wall -Wextra -g -DNDEBUG -DSTM32F401xE -DHSE_VALUE=8000000 -I"../include" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\Gpt" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\Gpio" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\Lib" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\Rcc" -I"../system/include" -I"../system/include/cmsis" -I"E:\THIRD YEAR\Second term\Embedded systems\Vehicle-Door-Handle-Control-Unit\DoorHandle\EXTI" -std=gnu11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


