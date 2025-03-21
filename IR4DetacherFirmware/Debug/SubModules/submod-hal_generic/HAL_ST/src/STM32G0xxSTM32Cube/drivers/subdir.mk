################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/drivers/uart_driver.c 

OBJS += \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/drivers/uart_driver.o 

C_DEPS += \
./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/drivers/uart_driver.d 


# Each subdirectory must supply rules for building sources it contributes
SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/drivers/%.o SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/drivers/%.su SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/drivers/%.cyclo: ../SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/drivers/%.c SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/drivers/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-hal_generic/HAL_Generic" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-hal_generic/HAL_Generic/drivers" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/HardwareAbstractionLayer/STM32G070xx/config/Inc" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-ir_comms" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-cyclic_fifo_queue" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-SubModules-2f-submod-2d-hal_generic-2f-HAL_ST-2f-src-2f-STM32G0xxSTM32Cube-2f-drivers

clean-SubModules-2f-submod-2d-hal_generic-2f-HAL_ST-2f-src-2f-STM32G0xxSTM32Cube-2f-drivers:
	-$(RM) ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/drivers/uart_driver.cyclo ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/drivers/uart_driver.d ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/drivers/uart_driver.o ./SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/drivers/uart_driver.su

.PHONY: clean-SubModules-2f-submod-2d-hal_generic-2f-HAL_ST-2f-src-2f-STM32G0xxSTM32Cube-2f-drivers

