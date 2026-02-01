################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/JBD_OLEDkeyboard/FlashFun.c \
../code/JBD_OLEDkeyboard/Font.c \
../code/JBD_OLEDkeyboard/JBD_simiic.c \
../code/JBD_OLEDkeyboard/OLEDKeyboard.c \
../code/JBD_OLEDkeyboard/UI.c \
../code/JBD_OLEDkeyboard/dev_CH455.c \
../code/JBD_OLEDkeyboard/dev_ssd1306.c 

COMPILED_SRCS += \
code/JBD_OLEDkeyboard/FlashFun.src \
code/JBD_OLEDkeyboard/Font.src \
code/JBD_OLEDkeyboard/JBD_simiic.src \
code/JBD_OLEDkeyboard/OLEDKeyboard.src \
code/JBD_OLEDkeyboard/UI.src \
code/JBD_OLEDkeyboard/dev_CH455.src \
code/JBD_OLEDkeyboard/dev_ssd1306.src 

C_DEPS += \
code/JBD_OLEDkeyboard/FlashFun.d \
code/JBD_OLEDkeyboard/Font.d \
code/JBD_OLEDkeyboard/JBD_simiic.d \
code/JBD_OLEDkeyboard/OLEDKeyboard.d \
code/JBD_OLEDkeyboard/UI.d \
code/JBD_OLEDkeyboard/dev_CH455.d \
code/JBD_OLEDkeyboard/dev_ssd1306.d 

OBJS += \
code/JBD_OLEDkeyboard/FlashFun.o \
code/JBD_OLEDkeyboard/Font.o \
code/JBD_OLEDkeyboard/JBD_simiic.o \
code/JBD_OLEDkeyboard/OLEDKeyboard.o \
code/JBD_OLEDkeyboard/UI.o \
code/JBD_OLEDkeyboard/dev_CH455.o \
code/JBD_OLEDkeyboard/dev_ssd1306.o 


# Each subdirectory must supply rules for building sources it contributes
code/JBD_OLEDkeyboard/FlashFun.src: ../code/JBD_OLEDkeyboard/FlashFun.c code/JBD_OLEDkeyboard/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
code/JBD_OLEDkeyboard/FlashFun.o: code/JBD_OLEDkeyboard/FlashFun.src code/JBD_OLEDkeyboard/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
code/JBD_OLEDkeyboard/Font.src: ../code/JBD_OLEDkeyboard/Font.c code/JBD_OLEDkeyboard/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
code/JBD_OLEDkeyboard/Font.o: code/JBD_OLEDkeyboard/Font.src code/JBD_OLEDkeyboard/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
code/JBD_OLEDkeyboard/JBD_simiic.src: ../code/JBD_OLEDkeyboard/JBD_simiic.c code/JBD_OLEDkeyboard/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
code/JBD_OLEDkeyboard/JBD_simiic.o: code/JBD_OLEDkeyboard/JBD_simiic.src code/JBD_OLEDkeyboard/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
code/JBD_OLEDkeyboard/OLEDKeyboard.src: ../code/JBD_OLEDkeyboard/OLEDKeyboard.c code/JBD_OLEDkeyboard/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
code/JBD_OLEDkeyboard/OLEDKeyboard.o: code/JBD_OLEDkeyboard/OLEDKeyboard.src code/JBD_OLEDkeyboard/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
code/JBD_OLEDkeyboard/UI.src: ../code/JBD_OLEDkeyboard/UI.c code/JBD_OLEDkeyboard/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
code/JBD_OLEDkeyboard/UI.o: code/JBD_OLEDkeyboard/UI.src code/JBD_OLEDkeyboard/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
code/JBD_OLEDkeyboard/dev_CH455.src: ../code/JBD_OLEDkeyboard/dev_CH455.c code/JBD_OLEDkeyboard/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
code/JBD_OLEDkeyboard/dev_CH455.o: code/JBD_OLEDkeyboard/dev_CH455.src code/JBD_OLEDkeyboard/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
code/JBD_OLEDkeyboard/dev_ssd1306.src: ../code/JBD_OLEDkeyboard/dev_ssd1306.c code/JBD_OLEDkeyboard/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
code/JBD_OLEDkeyboard/dev_ssd1306.o: code/JBD_OLEDkeyboard/dev_ssd1306.src code/JBD_OLEDkeyboard/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-code-2f-JBD_OLEDkeyboard

clean-code-2f-JBD_OLEDkeyboard:
	-$(RM) code/JBD_OLEDkeyboard/FlashFun.d code/JBD_OLEDkeyboard/FlashFun.o code/JBD_OLEDkeyboard/FlashFun.src code/JBD_OLEDkeyboard/Font.d code/JBD_OLEDkeyboard/Font.o code/JBD_OLEDkeyboard/Font.src code/JBD_OLEDkeyboard/JBD_simiic.d code/JBD_OLEDkeyboard/JBD_simiic.o code/JBD_OLEDkeyboard/JBD_simiic.src code/JBD_OLEDkeyboard/OLEDKeyboard.d code/JBD_OLEDkeyboard/OLEDKeyboard.o code/JBD_OLEDkeyboard/OLEDKeyboard.src code/JBD_OLEDkeyboard/UI.d code/JBD_OLEDkeyboard/UI.o code/JBD_OLEDkeyboard/UI.src code/JBD_OLEDkeyboard/dev_CH455.d code/JBD_OLEDkeyboard/dev_CH455.o code/JBD_OLEDkeyboard/dev_CH455.src code/JBD_OLEDkeyboard/dev_ssd1306.d code/JBD_OLEDkeyboard/dev_ssd1306.o code/JBD_OLEDkeyboard/dev_ssd1306.src

.PHONY: clean-code-2f-JBD_OLEDkeyboard

