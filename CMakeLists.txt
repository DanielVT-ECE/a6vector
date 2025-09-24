cmake_minimum_required(VERSION 3.10)
# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# used internally by CMake to identify your project
project(a6vector)

# Include the directory headers are located
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the main executable (include vector implementation so templates are available)
add_executable(a6vector src/main.cpp src/vector.cpp)

####################################################
# Add the test executable (link vector implementation into the test binary)
add_executable(my_test src/vector.cpp tests/test.cpp)
# Include directories for the test target
target_include_directories(my_test PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/catch2)
# Enable testing
enable_testing()
# Register the test executable with CTest (optional)
add_test(NAME my_test COMMAND my_test)
