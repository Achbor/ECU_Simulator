cmake_minimum_required(VERSION 3.16)

project(ECUSimulator C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(ecu_simulator
	src/main.c
	src/can.c
	src/ecu.c
	src/ecu_manager.c
	src/engine.c
	src/sensors.c
	src/can.c
	src/logger.c
	src/cli.c
	src/fault_manager.c
	src/scheduler.c
	src/system.c
)

target_link_libraries(ecu_simulator pthread)
