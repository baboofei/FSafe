#=============================================================================#
# Author: QueezyTheGreat                                                      #
# Date:   26.04.2011                                                          #
#                                                                             #
# Description: Arduino CMake example                                          #
#                                                                             #
#=============================================================================#
set(CMAKE_TOOLCHAIN_FILE arduino-cmake/cmake/ArduinoToolchain.cmake) # Arduino Toolchain

set(ARDUINO_DEFAULT_BOARD uno) # Default Board ID, when not specified
set(ARDUINO_DEFAULT_PORT /dev/ttyACM0) # Default Port, when not specified

cmake_minimum_required(VERSION 2.8)
#====================================================================#
#  Setup Project                                                     #
#====================================================================#
project(DiceRoller C CXX)

print_board_list()
print_programmer_list()

#	Default debug build
generate_arduino_firmware(arduos
	SRCS		./arduos.cpp
	BOARD 		uno
	PORT		/dev/ttyACM0
	SERIAL 		screen @SERIAL_PORT@
	)

#	Default production build
generate_arduino_firmware(arduos-production
	SRCS 		./arduos.cpp
	BOARD		uno
	PORT 		/dev/ttyACM0
	SERIAL 		screen @SERIAL_PORT@
	)


