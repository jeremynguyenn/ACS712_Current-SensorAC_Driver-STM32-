################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/acs712.c \
../Src/delay.c \
../Src/i2c.c \
../Src/lcd.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/uart.c 

OBJS += \
./Src/acs712.o \
./Src/delay.o \
./Src/i2c.o \
./Src/lcd.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/uart.o 

C_DEPS += \
./Src/acs712.d \
./Src/delay.d \
./Src/i2c.d \
./Src/lcd.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32F411xE=STM32F411xE -c -I"/Users/hussamaldean/STM32CubeIDE/workspace_1.7.0/embeddedExpertIO_posts/ACS712_Current_Sensor_AC_Current/Inc" -I"/Users/hussamaldean/STM32CubeIDE/workspace_1.7.0/embeddedExpertIO_posts/ACS712_Current_Sensor_AC_Current/chip header/CMSIS/Device/ST/STM32F4xx/Include" -I"/Users/hussamaldean/STM32CubeIDE/workspace_1.7.0/embeddedExpertIO_posts/ACS712_Current_Sensor_AC_Current/chip header/CMSIS/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/acs712.d ./Src/acs712.o ./Src/acs712.su ./Src/delay.d ./Src/delay.o ./Src/delay.su ./Src/i2c.d ./Src/i2c.o ./Src/i2c.su ./Src/lcd.d ./Src/lcd.o ./Src/lcd.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/uart.d ./Src/uart.o ./Src/uart.su

.PHONY: clean-Src

