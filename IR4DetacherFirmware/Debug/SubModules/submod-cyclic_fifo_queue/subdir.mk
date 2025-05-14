################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue.c \
../SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue_test.c 

OBJS += \
./SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue.o \
./SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue_test.o 

C_DEPS += \
./SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue.d \
./SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue_test.d 


# Each subdirectory must supply rules for building sources it contributes
SubModules/submod-cyclic_fifo_queue/%.o SubModules/submod-cyclic_fifo_queue/%.su SubModules/submod-cyclic_fifo_queue/%.cyclo: ../SubModules/submod-cyclic_fifo_queue/%.c SubModules/submod-cyclic_fifo_queue/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G070xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/Application/flash_controller" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/Application/fwVersion/Inc" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/Application/ir_key_glue" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/Application/IRComms/Inc" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/Application/NFC/Inc" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/Application/Piezo/Inc" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/Application/Vboost/Inc" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/Application/WirelessPwrTransfer/Inc" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-hal_generic/HAL_Generic" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-hal_generic/HAL_Generic/drivers" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/HardwareAbstractionLayer/STM32G070xx/config/Inc" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-ir_comms" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-cyclic_fifo_queue" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-NTAG_NFC" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod-flash_controller" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/HardwareAbstractionLayer/STM32G070xx" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod_segger-RTT-debugging/DebugWrapper" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod_segger-RTT-debugging/SEGGER_RTT/RTT" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/Application/Utils/Inc" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/Application/flash_controller/Inc" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod_segger-RTT-debugging/SEGGER_RTT" -I"C:/Users/jpieterick/Desktop/Projects/F1888IR4OneKeyDetacher/firmware/F18888-IR4_DETACHER2.0/IR4DetacherFirmware/SubModules/submod_segger-RTT-debugging" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-SubModules-2f-submod-2d-cyclic_fifo_queue

clean-SubModules-2f-submod-2d-cyclic_fifo_queue:
	-$(RM) ./SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue.cyclo ./SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue.d ./SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue.o ./SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue.su ./SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue_test.cyclo ./SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue_test.d ./SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue_test.o ./SubModules/submod-cyclic_fifo_queue/cyclic_fifo_queue_test.su

.PHONY: clean-SubModules-2f-submod-2d-cyclic_fifo_queue

