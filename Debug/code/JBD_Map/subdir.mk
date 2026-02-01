################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/JBD_Map/Map.c 

COMPILED_SRCS += \
code/JBD_Map/Map.src 

C_DEPS += \
code/JBD_Map/Map.d 

OBJS += \
code/JBD_Map/Map.o 


# Each subdirectory must supply rules for building sources it contributes
code/JBD_Map/Map.src: ../code/JBD_Map/Map.c code/JBD_Map/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
code/JBD_Map/Map.o: code/JBD_Map/Map.src code/JBD_Map/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-code-2f-JBD_Map

clean-code-2f-JBD_Map:
	-$(RM) code/JBD_Map/Map.d code/JBD_Map/Map.o code/JBD_Map/Map.src

.PHONY: clean-code-2f-JBD_Map

