################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/zf_device/zf_device_dot_matrix_screen.c \
../libraries/zf_device/zf_device_gnss.c \
../libraries/zf_device/zf_device_icm20602.c \
../libraries/zf_device/zf_device_imu660ra.c \
../libraries/zf_device/zf_device_imu963ra.c \
../libraries/zf_device/zf_device_tld7002.c \
../libraries/zf_device/zf_device_type.c 

COMPILED_SRCS += \
libraries/zf_device/zf_device_dot_matrix_screen.src \
libraries/zf_device/zf_device_gnss.src \
libraries/zf_device/zf_device_icm20602.src \
libraries/zf_device/zf_device_imu660ra.src \
libraries/zf_device/zf_device_imu963ra.src \
libraries/zf_device/zf_device_tld7002.src \
libraries/zf_device/zf_device_type.src 

C_DEPS += \
libraries/zf_device/zf_device_dot_matrix_screen.d \
libraries/zf_device/zf_device_gnss.d \
libraries/zf_device/zf_device_icm20602.d \
libraries/zf_device/zf_device_imu660ra.d \
libraries/zf_device/zf_device_imu963ra.d \
libraries/zf_device/zf_device_tld7002.d \
libraries/zf_device/zf_device_type.d 

OBJS += \
libraries/zf_device/zf_device_dot_matrix_screen.o \
libraries/zf_device/zf_device_gnss.o \
libraries/zf_device/zf_device_icm20602.o \
libraries/zf_device/zf_device_imu660ra.o \
libraries/zf_device/zf_device_imu963ra.o \
libraries/zf_device/zf_device_tld7002.o \
libraries/zf_device/zf_device_type.o 


# Each subdirectory must supply rules for building sources it contributes
libraries/zf_device/zf_device_dot_matrix_screen.src: ../libraries/zf_device/zf_device_dot_matrix_screen.c libraries/zf_device/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
libraries/zf_device/zf_device_dot_matrix_screen.o: libraries/zf_device/zf_device_dot_matrix_screen.src libraries/zf_device/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
libraries/zf_device/zf_device_gnss.src: ../libraries/zf_device/zf_device_gnss.c libraries/zf_device/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
libraries/zf_device/zf_device_gnss.o: libraries/zf_device/zf_device_gnss.src libraries/zf_device/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
libraries/zf_device/zf_device_icm20602.src: ../libraries/zf_device/zf_device_icm20602.c libraries/zf_device/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
libraries/zf_device/zf_device_icm20602.o: libraries/zf_device/zf_device_icm20602.src libraries/zf_device/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
libraries/zf_device/zf_device_imu660ra.src: ../libraries/zf_device/zf_device_imu660ra.c libraries/zf_device/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
libraries/zf_device/zf_device_imu660ra.o: libraries/zf_device/zf_device_imu660ra.src libraries/zf_device/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
libraries/zf_device/zf_device_imu963ra.src: ../libraries/zf_device/zf_device_imu963ra.c libraries/zf_device/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
libraries/zf_device/zf_device_imu963ra.o: libraries/zf_device/zf_device_imu963ra.src libraries/zf_device/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
libraries/zf_device/zf_device_tld7002.src: ../libraries/zf_device/zf_device_tld7002.c libraries/zf_device/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
libraries/zf_device/zf_device_tld7002.o: libraries/zf_device/zf_device_tld7002.src libraries/zf_device/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
libraries/zf_device/zf_device_type.src: ../libraries/zf_device/zf_device_type.c libraries/zf_device/subdir.mk
	cctc -cs --dep-file="$(*F).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS/26_V0.0_Bike_KModel/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<"
libraries/zf_device/zf_device_type.o: libraries/zf_device/zf_device_type.src libraries/zf_device/subdir.mk
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"

clean: clean-libraries-2f-zf_device

clean-libraries-2f-zf_device:
	-$(RM) libraries/zf_device/zf_device_dot_matrix_screen.d libraries/zf_device/zf_device_dot_matrix_screen.o libraries/zf_device/zf_device_dot_matrix_screen.src libraries/zf_device/zf_device_gnss.d libraries/zf_device/zf_device_gnss.o libraries/zf_device/zf_device_gnss.src libraries/zf_device/zf_device_icm20602.d libraries/zf_device/zf_device_icm20602.o libraries/zf_device/zf_device_icm20602.src libraries/zf_device/zf_device_imu660ra.d libraries/zf_device/zf_device_imu660ra.o libraries/zf_device/zf_device_imu660ra.src libraries/zf_device/zf_device_imu963ra.d libraries/zf_device/zf_device_imu963ra.o libraries/zf_device/zf_device_imu963ra.src libraries/zf_device/zf_device_tld7002.d libraries/zf_device/zf_device_tld7002.o libraries/zf_device/zf_device_tld7002.src libraries/zf_device/zf_device_type.d libraries/zf_device/zf_device_type.o libraries/zf_device/zf_device_type.src

.PHONY: clean-libraries-2f-zf_device

