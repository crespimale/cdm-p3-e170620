################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/MCUinit.c" \
"../Sources/SCI.c" \
"../Sources/TASK.c" \
"../Sources/TPM.c" \
"../Sources/main.c" \

C_SRCS += \
../Sources/MCUinit.c \
../Sources/SCI.c \
../Sources/TASK.c \
../Sources/TPM.c \
../Sources/main.c \

OBJS += \
./Sources/MCUinit_c.obj \
./Sources/SCI_c.obj \
./Sources/TASK_c.obj \
./Sources/TPM_c.obj \
./Sources/main_c.obj \

OBJS_QUOTED += \
"./Sources/MCUinit_c.obj" \
"./Sources/SCI_c.obj" \
"./Sources/TASK_c.obj" \
"./Sources/TPM_c.obj" \
"./Sources/main_c.obj" \

C_DEPS += \
./Sources/MCUinit_c.d \
./Sources/SCI_c.d \
./Sources/TASK_c.d \
./Sources/TPM_c.d \
./Sources/main_c.d \

OBJS_OS_FORMAT += \
./Sources/MCUinit_c.obj \
./Sources/SCI_c.obj \
./Sources/TASK_c.obj \
./Sources/TPM_c.obj \
./Sources/main_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/MCUinit_c.obj: ../Sources/MCUinit.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/MCUinit.args" -ObjN="Sources/MCUinit_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/SCI_c.obj: ../Sources/SCI.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SCI.args" -ObjN="Sources/SCI_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/TASK_c.obj: ../Sources/TASK.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/TASK.args" -ObjN="Sources/TASK_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/TPM_c.obj: ../Sources/TPM.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/TPM.args" -ObjN="Sources/TPM_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


