cmake_minimum_required(VERSION 3.7)
project(PeaKTrace)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_MODULE_PATH /usr/share/cmake-3.22/Modules)

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
add_executable(PeaKTrace ${PeaKTrace_SOURCES} scripts/header/tracer.h scripts/source/tracer.cpp scripts/header/world.h scripts/header/camera.h scripts/header/math/vector.h scripts/header/light.h scripts/source/light.cpp scripts/source/world.cpp scripts/header/object/object.h scripts/header/object/sphere.h scripts/source/math/vector.cpp scripts/header/math/trig.h header/misc/abs.h scripts/header/math/ray.h scripts/header/math/collisionResult.h scripts/source/object/sphere.cpp scripts/source/object/object.cpp scripts/source/camera.cpp scripts/header/math/degRad.h config/tracerConfig.h)

target_link_libraries(PeaKTrace ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES} Threads::Threads)