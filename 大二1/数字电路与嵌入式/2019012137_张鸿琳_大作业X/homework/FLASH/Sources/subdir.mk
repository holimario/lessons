################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/OLED.c" \
"../Sources/handle.c" \
"../Sources/main.c" \
"../Sources/sa_mtb.c" \
"../Sources/sound.c" \

C_SRCS += \
../Sources/OLED.c \
../Sources/handle.c \
../Sources/main.c \
../Sources/sa_mtb.c \
../Sources/sound.c \

OBJS += \
./Sources/OLED.o \
./Sources/handle.o \
./Sources/main.o \
./Sources/sa_mtb.o \
./Sources/sound.o \

C_DEPS += \
./Sources/OLED.d \
./Sources/handle.d \
./Sources/main.d \
./Sources/sa_mtb.d \
./Sources/sound.d \

OBJS_QUOTED += \
"./Sources/OLED.o" \
"./Sources/handle.o" \
"./Sources/main.o" \
"./Sources/sa_mtb.o" \
"./Sources/sound.o" \

C_DEPS_QUOTED += \
"./Sources/OLED.d" \
"./Sources/handle.d" \
"./Sources/main.d" \
"./Sources/sa_mtb.d" \
"./Sources/sound.d" \

OBJS_OS_FORMAT += \
./Sources/OLED.o \
./Sources/handle.o \
./Sources/main.o \
./Sources/sa_mtb.o \
./Sources/sound.o \


# Each subdirectory must supply rules for building sources it contributes
Sources/OLED.o: ../Sources/OLED.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/OLED.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/OLED.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/handle.o: ../Sources/handle.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/handle.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/handle.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/main.o: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/main.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/main.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sa_mtb.o: ../Sources/sa_mtb.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sa_mtb.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sa_mtb.o"
	@echo 'Finished building: $<'
	@echo ' '

Sources/sound.o: ../Sources/sound.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: ARM Ltd Windows GCC C Compiler'
	"$(ARMSourceryDirEnv)/arm-none-eabi-gcc" "$<" @"Sources/sound.args" -MMD -MP -MF"$(@:%.o=%.d)" -o"Sources/sound.o"
	@echo 'Finished building: $<'
	@echo ' '


