################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HardwareAbstractionLayer/STM32G070xx/hardware_abstraction_layer.c \
../HardwareAbstractionLayer/STM32G070xx/startup.c 

OBJS += \
./HardwareAbstractionLayer/STM32G070xx/hardware_abstraction_layer.o \
./HardwareAbstractionLayer/STM32G070xx/startup.o 

C_DEPS += \
./HardwareAbstractionLayer/STM32G070xx/hardware_abstraction_layer.d \
./HardwareAbstractionLayer/STM32G070xx/startup.d 


# Each subdirectory must supply rules for building sources it contributes
HardwareAbstractionLayer/STM32G070xx/%.o HardwareAbstractionLayer/STM32G070xx/%.su HardwareAbstractionLayer/STM32G070xx/%.cyclo: ../HardwareAbstractionLayer/STM32G070xx/%.c HardwareAbstractionLayer/STM32G070xx/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-hal_generic/HAL_Generic" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-hal_generic/HAL_Generic/drivers" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/HardwareAbstractionLayer/STM32G070xx/config/Inc" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-ir_comms" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-cyclic_fifo_queue" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HardwareAbstractionLayer-2f-STM32G070xx

clean-HardwareAbstractionLayer-2f-STM32G070xx:
	-$(RM) ./HardwareAbstractionLayer/STM32G070xx/hardware_abstraction_layer.cyclo ./HardwareAbstractionLayer/STM32G070xx/hardware_abstraction_layer.d ./HardwareAbstractionLayer/STM32G070xx/hardware_abstraction_layer.o ./HardwareAbstractionLayer/STM32G070xx/hardware_abstraction_layer.su ./HardwareAbstractionLayer/STM32G070xx/startup.cyclo ./HardwareAbstractionLayer/STM32G070xx/startup.d ./HardwareAbstractionLayer/STM32G070xx/startup.o ./HardwareAbstractionLayer/STM32G070xx/startup.su

.PHONY: clean-HardwareAbstractionLayer-2f-STM32G070xx

