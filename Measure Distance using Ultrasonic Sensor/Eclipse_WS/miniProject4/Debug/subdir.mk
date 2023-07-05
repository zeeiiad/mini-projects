################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MY_GPIO.c \
../MeasureDistance.c \
../My_LCD.c \
../icu.c \
../ultrasonic.c 

OBJS += \
./MY_GPIO.o \
./MeasureDistance.o \
./My_LCD.o \
./icu.o \
./ultrasonic.o 

C_DEPS += \
./MY_GPIO.d \
./MeasureDistance.d \
./My_LCD.d \
./icu.d \
./ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


