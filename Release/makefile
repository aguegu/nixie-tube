################################################################################
# 自动生成的文件。不要编辑！
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include NixieTube/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
nixie-tube.lss \

FLASH_IMAGE += \
nixie-tube.hex \

EEPROM_IMAGE += \
nixie-tube.eep \

SIZEDUMMY += \
sizedummy \


# 所有目标
all: nixie-tube.elf secondary-outputs

# 工具调用
nixie-tube.elf: $(OBJS) $(USER_OBJS)
	@echo '正在构建目标： $@'
	@echo '正在调用： AVR C++ Linker'
	avr-gcc -Os -Wl,--gc-sections  -L"H:\workspace\myArduinoLibs\Arduino_Uno/Release" -mmcu=atmega328p -o"nixie-tube.elf" $(OBJS) $(USER_OBJS) $(LIBS) -lm
	@echo '已结束构建目标： $@'
	@echo ' '

nixie-tube.lss: nixie-tube.elf
	@echo '正在调用： AVR Create Extended Listing'
	-avr-objdump -h -S nixie-tube.elf  >"nixie-tube.lss"
	@echo '已结束构建： $@'
	@echo ' '

nixie-tube.hex: nixie-tube.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -O ihex nixie-tube.elf  "nixie-tube.hex"
	@echo '已结束构建： $@'
	@echo ' '

nixie-tube.eep: nixie-tube.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex nixie-tube.elf  "nixie-tube.eep"
	@echo '已结束构建： $@'
	@echo ' '

sizedummy: nixie-tube.elf
	@echo '正在调用： Print Size'
	-avr-size --format=avr --mcu=atmega328p nixie-tube.elf
	@echo '已结束构建： $@'
	@echo ' '

# 其他目标
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EEPROM_IMAGE)$(ELFS)$(FLASH_IMAGE)$(LSS)$(S_DEPS)$(CXX_DEPS)$(S_UPPER_DEPS)$(C++_DEPS)$(ASM_DEPS)$(CC_DEPS)$(CPP_DEPS)$(C_UPPER_DEPS)$(SIZEDUMMY) nixie-tube.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
