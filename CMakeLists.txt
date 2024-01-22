cmake_minimum_required(VERSION 3.7)
project(PeaKTrace)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH /usr/share/cmake/Modules)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_definitions(-DPEAK_ENGINE_DEBUG_MODE=1)
else()
    add_definitions(-DPEAK_ENGINE_DEBUG_MODE=0)
endif()

message(STATUS ${CMAKE_MODULE_PATH})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIR})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/header/")
include_directories("${PROJECT_SOURCE_DIR}/scripts/header/")
include_directories("${PROJECT_SOURCE_DIR}/config/")

file(GLOB_RECURSE PeaKTrace_SOURCES CONFIGURE_DEPENDS "*.cpp")
list(FILTER PeaKTrace_SOURCES EXCLUDE REGEX ".*cmake-build-debug.*")
list(FILTER PeaKTrace_SOURCES EXCLUDE REGEX ".*cmake-build-release.*")

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_definitions(-DPEAK_ENGINE_DEBUG_MODE=1)
else()
    add_definitions(-DPEAK_ENGINE_DEBUG_MODE=0)
endif()

add_executable(PeaKTrace ${PeaKTrace_SOURCES})

target_link_libraries(PeaKTrace ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} Threads::Threads)