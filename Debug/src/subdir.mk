################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/camera.cpp \
../src/main.cpp \
../src/scene.cpp \
../src/utils.cpp \
../src/x_window.cpp 

OBJS += \
./src/camera.o \
./src/main.o \
./src/scene.o \
./src/utils.o \
./src/x_window.o 

CPP_DEPS += \
./src/camera.d \
./src/main.d \
./src/scene.d \
./src/utils.d \
./src/x_window.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=gnu++11 -O0 -pedantic -Wall -Wextra -c -fmessage-length=0 -ffast-math -m64 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


