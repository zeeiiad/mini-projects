################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Buzzer.c \
../Ctrl_APP_Layer.c \
../DcMotor.c \
../EEPROM.c \
../GPIO.c \
../I2C.c \
../PWM_Timer0.c \
../Timer1.c \
../UART.c 

OBJS += \
./Buzzer.o \
./Ctrl_APP_Layer.o \
./DcMotor.o \
./EEPROM.o \
./GPIO.o \
./I2C.o \
./PWM_Timer0.o \
./Timer1.o \
./UART.o 

C_DEPS += \
./Buzzer.d \
./Ctrl_APP_Layer.d \
./DcMotor.d \
./EEPROM.d \
./GPIO.d \
./I2C.d \
./PWM_Timer0.d \
./Timer1.d \
./UART.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


