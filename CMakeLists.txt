cmake_minimum_required(VERSION 2.8.3)
project(unitree_legged_sdk)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -fPIC")

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(ARCH amd64)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(ARCH arm64)
endif()

include_directories(include)
link_directories(lib/cpp/${ARCH})
set(EXTRA_LIBS -pthread libunitree_legged_sdk.so lcm)

# Ask the installed pybind11 Python package where its CMake config lives,
# so find_package() can locate it without a vendored copy.
if(NOT PYTHON_EXECUTABLE)
    set(PYTHON_EXECUTABLE python3)
endif()
execute_process(
    COMMAND ${PYTHON_EXECUTABLE} -c "import pybind11; print(pybind11.get_cmake_dir())"
    OUTPUT_VARIABLE pybind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_QUIET
)
find_package(pybind11 REQUIRED)

# examples (target name = source name without the _sport suffix)
foreach(SRC walk_aliengo_sport start_aliengo_sport joystick_aliengo_sport
        recovery_aliengo_sport position_aliengo velocity_aliengo torque_aliengo)
    string(REPLACE "_sport" "" TARGET ${SRC})
    add_executable(example_${TARGET} examples/example_${SRC}.cpp)
    target_link_libraries(example_${TARGET} ${EXTRA_LIBS})
endforeach()

# python wrapper
pybind11_add_module(robot_interface python_wrapper/python_interface.cpp)
target_link_libraries(robot_interface PRIVATE ${EXTRA_LIBS})
set_target_properties(robot_interface PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/python/${ARCH}
    # Resolve libunitree_legged_sdk.so relative to this module at runtime:
    # lib/python/${ARCH} -> lib/cpp/${ARCH}. $ORIGIN keeps it relocatable.
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "$ORIGIN/../../cpp/${ARCH}"
)
