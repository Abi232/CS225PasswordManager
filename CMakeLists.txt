cmake_minimum_required(VERSION 3.1)
project(blowfish VERSION 1.0.0 LANGUAGES CXX)

# Verify project source
message(STATUS "PROJECT_SOURCE_DIR is: ${PROJECT_SOURCE_DIR}")

# Set the C++ standard to 14
if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
elseif (CMAKE_CXX_STANDARD LESS 11)
    message(WARNING "CMAKE_CXX_STANDARD has been set to '${CMAKE_CXX_STANDARD}' which is lower than the minimum required standard (c++14).")
endif()

message(STATUS "Using C++ standard c++${CMAKE_CXX_STANDARD}")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Additional project information, typical cmake print
message(STATUS "CMake version: ${CMAKE_VERSION}")
message(STATUS "Project version: ${PROJECT_VERSION}")

# Set source files for Blowfish library inc
set(BLOWFISH_SRC ${PROJECT_SOURCE_DIR}/src/blowfish.cc)
set(BLOWFISH2_SRC ${PROJECT_SOURCE_DIR}/src/blowfish2.cc)

# CS225 source files
set(ABIPROJECT_SRC 
    ${PROJECT_SOURCE_DIR}/tests/CS225Project/databaseReadValidate.cpp
    ${PROJECT_SOURCE_DIR}/tests/CS225Project/encryptEntryAddDatabase.cpp
    ${PROJECT_SOURCE_DIR}/tests/CS225Project/passwordGenerator.cpp
    ${PROJECT_SOURCE_DIR}/tests/CS225Project/processUserLogin.cpp
)

# Set all test files
set(ABIPROJECT_TEST ${PROJECT_SOURCE_DIR}/tests/CS225Project/main.cpp)
set(BLOWFISH2_TEST ${PROJECT_SOURCE_DIR}/tests/Main2.cpp)

# Path to libraries included
set(BLOWFISH_INC ${PROJECT_SOURCE_DIR}/include)
set(ABIPROJECT_INC ${PROJECT_SOURCE_DIR}/tests/CS225Project)

# Create libraries
add_library(abiproject STATIC
    ${BLOWFISH_SRC}
    ${ABIPROJECT_SRC}
)

add_library(blowfish2 STATIC
    ${BLOWFISH2_SRC}
)

# Create executables
add_executable(abiproject_test
    ${ABIPROJECT_TEST}
)

add_executable(bf2_test
    ${BLOWFISH2_TEST}
)

# Target include directories for libraries and executables
target_include_directories(abiproject PUBLIC
    ${BLOWFISH_INC}
    ${ABIPROJECT_INC}
)

target_include_directories(blowfish2 PUBLIC
    ${BLOWFISH_INC}
)

target_include_directories(abiproject_test PRIVATE
    ${ABIPROJECT_INC}
    ${BLOWFISH_INC}
)

target_include_directories(bf2_test PRIVATE
    ${BLOWFISH_INC}
)

# Link executables to their corresponding libraries
target_link_libraries(abiproject_test PRIVATE abiproject)
target_link_libraries(bf2_test PRIVATE blowfish2)
