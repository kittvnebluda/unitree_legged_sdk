cmake_minimum_required(VERSION 2.8.3)
project(unitree_legged_sdk)

include_directories(include)
include_directories(./)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PYTHON_BUILD TRUE)

execute_process(
    COMMAND ${PYTHON_EXECUTABLE} -c "import pybind11; print(pybind11.get_cmake_dir())"
    OUTPUT_VARIABLE pybind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)
find_package(pybind11 REQUIRED)

link_directories(lib/cpp/amd64)

add_compile_options(-std=c++14)

message("-- CMAKE_SYSTEM_PROCESSOR: ${CMAKE_SYSTEM_PROCESSOR}")
if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "x86_64.*")
    set(ARCH amd64)
endif()
if("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "aarch64.*")
    set(ARCH arm64)
endif()

link_directories(lib/cpp/${ARCH})
set(EXTRA_LIBS -pthread libunitree_legged_sdk.so lcm)

set(CMAKE_CXX_FLAGS "-O3 -fPIC")

add_executable(example_walk_aliengo examples/example_walk_aliengo_sport.cpp)
target_link_libraries(example_walk_aliengo ${EXTRA_LIBS})

add_executable(example_start_aliengo examples/example_start_aliengo_sport.cpp)
target_link_libraries(example_start_aliengo ${EXTRA_LIBS})

add_executable(example_joystick_aliengo examples/example_joystick_aliengo_sport.cpp)
target_link_libraries(example_joystick_aliengo ${EXTRA_LIBS})

add_executable(example_recovery_aliengo examples/example_recovery_aliengo_sport.cpp)
target_link_libraries(example_recovery_aliengo ${EXTRA_LIBS})

add_executable(example_position_aliengo examples/example_position_aliengo.cpp)
target_link_libraries(example_position_aliengo ${EXTRA_LIBS})

add_executable(example_velocity_aliengo examples/example_velocity_aliengo.cpp)
target_link_libraries(example_velocity_aliengo ${EXTRA_LIBS})

add_executable(example_torque_aliengo examples/example_torque_aliengo.cpp)
target_link_libraries(example_torque_aliengo ${EXTRA_LIBS})


pybind11_add_module(robot_interface python_wrapper/python_interface.cpp)
target_compile_options(robot_interface PRIVATE -fPIC -no-pie)
set_target_properties(robot_interface PROPERTIES
      LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/python/${ARCH}
)
