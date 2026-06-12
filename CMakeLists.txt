cmake_minimum_required(VERSION 2.8.3)
project(unitree_legged_sdk)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-O3 -fPIC")
# The prebuilt static SDK lib is not PIE-compatible; modern GCC links
# executables as PIE by default, so disable it for the examples.
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -no-pie")

if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(ARCH amd64)
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(ARCH arm64)
endif()

include_directories(include)
link_directories(lib/cpp/${ARCH})
set(EXTRA_LIBS -pthread libunitree_legged_sdk.a)

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

find_package(catkin QUIET)
if(catkin_FOUND)
    catkin_package(
        INCLUDE_DIRS include
        LIBRARIES ${PROJECT_SOURCE_DIR}/lib/cpp/${ARCH}/libunitree_legged_sdk.a
    )
endif()

# examples
foreach(EXAMPLE position velocity torque walk joystick)
    add_executable(example_${EXAMPLE} example/example_${EXAMPLE}.cpp)
    target_link_libraries(example_${EXAMPLE} ${EXTRA_LIBS})
    list(APPEND EXAMPLES example_${EXAMPLE})
endforeach()

# python wrapper
pybind11_add_module(robot_interface python_wrapper/python_interface.cpp)
target_link_libraries(robot_interface PRIVATE ${EXTRA_LIBS})
set_target_properties(robot_interface PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/python/${ARCH}
)

# install
install(TARGETS ${EXAMPLES} DESTINATION bin/unitree)
install(DIRECTORY lib/cpp/${ARCH}/ DESTINATION lib/unitree USE_SOURCE_PERMISSIONS)
