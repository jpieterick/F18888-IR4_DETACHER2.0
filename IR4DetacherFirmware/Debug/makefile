################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include SubModules/submod_segger-RTT-debugging/SEGGER_RTT/Syscalls/subdir.mk
-include SubModules/submod_segger-RTT-debugging/SEGGER_RTT/RTT/subdir.mk
-include SubModules/submod_segger-RTT-debugging/DebugWrapper/subdir.mk
-include SubModules/submod-ir_comms/subdir.mk
-include SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/drivers/subdir.mk
-include SubModules/submod-hal_generic/HAL_ST/src/STM32G0xxSTM32Cube/subdir.mk
-include SubModules/submod-flash_controller/subdir.mk
-include SubModules/submod-cyclic_fifo_queue/subdir.mk
-include HardwareAbstractionLayer/STM32G070xx/config/Src/subdir.mk
-include HardwareAbstractionLayer/STM32G070xx/subdir.mk
-include Drivers/STM32G0xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Application/uarts_glue/Src/subdir.mk
-include Application/uartTemp/subdir.mk
-include Application/ir_key_glue/subdir.mk
-include Application/fwVersion/Src/subdir.mk
-include Application/flash_controller/Src/subdir.mk
-include Application/WirelessPwrTransfer/Src/subdir.mk
-include Application/Vboost/Src/subdir.mk
-include Application/Utils/Src/subdir.mk
-include Application/Piezo/Src/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := F1800IR4DetacherFirmware
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
F1800IR4DetacherFirmware.elf \

MAP_FILES += \
F1800IR4DetacherFirmware.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
F1800IR4DetacherFirmware.list \

OBJCOPY_BIN += \
F1800IR4DetacherFirmware.bin \


# All Target
all: main-build

# Main-build Target
main-build: F1800IR4DetacherFirmware.elf secondary-outputs

# Tool invocations
F1800IR4DetacherFirmware.elf F1800IR4DetacherFirmware.map: $(OBJS) $(USER_OBJS) C:\Users\jpieterick\Desktop\Projects\F1888IR4OneKeyDetacher\firmware\F18888-IR4_DETACHER2.0\IR4DetacherFirmware\STM32G070CBTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "F1800IR4DetacherFirmware.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"C:\Users\jpieterick\Desktop\Projects\F1888IR4OneKeyDetacher\firmware\F18888-IR4_DETACHER2.0\IR4DetacherFirmware\STM32G070CBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="F1800IR4DetacherFirmware.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

F1800IR4DetacherFirmware.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "F1800IR4DetacherFirmware.list"
	@echo 'Finished building: $@'
	@echo ' '

F1800IR4DetacherFirmware.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "F1800IR4DetacherFirmware.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) F1800IR4DetacherFirmware.bin F1800IR4DetacherFirmware.elf F1800IR4DetacherFirmware.list F1800IR4DetacherFirmware.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
