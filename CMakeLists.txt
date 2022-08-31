cmake_minimum_required(VERSION 3.7)
project(PeaKTrace)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH /usr/share/cmake-3.22/Modules)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin/)

message(STATUS "Build type: ${MAKE_BUILD_TYPE}")

if (${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_definitions(-DPEAK_ENGINE_DEBUG_MODE=1)
else()
    add_definitions(-DPEAK_ENGINE_DEBUG_MODE=0)
endif()

message(STATUS ${CMAKE_MODULE_PATH})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(SDL2_TTF REQUIRED)
include_directories(${SDL2_TTF_INCLUDE_DIRS})

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

add_executable(PeaKTrace ${PeaKTrace_SOURCES} scripts/header/object/cube.h scripts/source/object/cube.cpp scripts/header/atmo/atmo.h scripts/header/atmo/globalHaze.h scripts/source/atmo/atmo.cpp scripts/source/atmo/globalHaze.cpp scripts/header/math/atmoResult.h scripts/header/math/random.h scripts/source/math/random.cpp scripts/source/atmo/sphereHaze.cpp scripts/header/atmo/sphereHaze.h scripts/header/math/noise.h scripts/header/math/lerp.h scripts/source/math/lerp.cpp scripts/source/math/noise.cpp)

target_link_libraries(PeaKTrace ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} Threads::Threads)