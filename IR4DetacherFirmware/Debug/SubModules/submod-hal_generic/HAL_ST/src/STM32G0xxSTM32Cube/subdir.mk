################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_cec.c \
../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_flash.c \
../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_gpio.c \
../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_i2c.c \
../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_init.c \
../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_interrupts.c \
../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_ram.c \
../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_rtc.c \
../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_spi.c \
../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_timer.c \
../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_uart.c \
../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_watchdog.c 

OBJS += \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_cec.o \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_flash.o \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_gpio.o \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_i2c.o \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_init.o \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_interrupts.o \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_ram.o \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_rtc.o \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_spi.o \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_timer.o \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_uart.o \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_watchdog.o 

C_DEPS += \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_cec.d \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_flash.d \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_gpio.d \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_i2c.d \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_init.d \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_interrupts.d \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_ram.d \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_rtc.d \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_spi.d \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_timer.d \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_uart.d \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_watchdog.d 


# Each subdirectory must supply rules for building sources it contributes
SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/%.o SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/%.su SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/%.cyclo: ../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/%.c SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-hal_generic/HAL_Generic" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-hal_generic/HAL_Generic/drivers" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/HardwareAbstractionLayer/STM32G070xx/config/Inc" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-ir_comms" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-cyclic_fifo_queue" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-SubModules-2f-submod-2d-hal_generic-2f-HAL_ST-2f-src-2f-STM32G0xxSTM32Cube

clean-SubModules-2f-submod-2d-hal_generic-2f-HAL_ST-2f-src-2f-STM32G0xxSTM32Cube:
	-$(RM) ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_cec.cyclo ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_cec.d ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_cec.o ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_cec.su ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_flash.cyclo ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_flash.d ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_flash.o ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_flash.su ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_gpio.cyclo ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_gpio.d ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_gpio.o ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_gpio.su ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_i2c.cyclo ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_i2c.d ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_i2c.o ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_i2c.su ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_init.cyclo ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_init.d ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_init.o ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_init.su ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_interrupts.cyclo ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_interrupts.d ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_interrupts.o ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_interrupts.su ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_ram.cyclo ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_ram.d ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_ram.o ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_ram.su ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_rtc.cyclo ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_rtc.d ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_rtc.o ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_rtc.su ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_spi.cyclo ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_spi.d ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_spi.o ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_spi.su ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_timer.cyclo ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_timer.d ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_timer.o ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_timer.su ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_uart.cyclo ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_uart.d ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_uart.o ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_uart.su ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_watchdog.cyclo ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_watchdog.d ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_watchdog.o ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/hal_watchdog.su

.PHONY: clean-SubModules-2f-submod-2d-hal_generic-2f-HAL_ST-2f-src-2f-STM32G0xxSTM32Cube

