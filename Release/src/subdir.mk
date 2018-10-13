################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/camera.cpp \
../src/main.cpp \
../src/utils.cpp \
../src/x_window.cpp 

OBJS += \
./src/camera.o \
./src/main.o \
./src/utils.o \
./src/x_window.o 

CPP_DEPS += \
./src/camera.d \
./src/main.d \
./src/utils.d \
./src/x_window.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


