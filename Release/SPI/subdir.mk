################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SPI/spi.c 

OBJS += \
./SPI/spi.o 

C_DEPS += \
./SPI/spi.d 


# Each subdirectory must supply rules for building sources it contributes
SPI/%.o: ../SPI/%.c SPI/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -Wno-deprecated-declarations -D__PROG_TYPES_COMPAT__ -mmcu=atmega32 -DF_CPU=11059200UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


