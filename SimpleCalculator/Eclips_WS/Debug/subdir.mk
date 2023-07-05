################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MY_GPIO.c \
../My_Keypad.c \
../My_LCD.c \
../Simple_calculator.c 

OBJS += \
./MY_GPIO.o \
./My_Keypad.o \
./My_LCD.o \
./Simple_calculator.o 

C_DEPS += \
./MY_GPIO.d \
./My_Keypad.d \
./My_LCD.d \
./Simple_calculator.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


