################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DcMotor.c \
../FanControllerSystem.c \
../Lm35_sensor.c \
../MY_GPIO.c \
../My_ADC.c \
../My_LCD.c \
../PWM_Timer0.c 

OBJS += \
./DcMotor.o \
./FanControllerSystem.o \
./Lm35_sensor.o \
./MY_GPIO.o \
./My_ADC.o \
./My_LCD.o \
./PWM_Timer0.o 

C_DEPS += \
./DcMotor.d \
./FanControllerSystem.d \
./Lm35_sensor.d \
./MY_GPIO.d \
./My_ADC.d \
./My_LCD.d \
./PWM_Timer0.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


