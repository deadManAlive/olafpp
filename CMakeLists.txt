cmake_minimum_required(VERSION 3.0.0)
project(OLaF VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    # temporary
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# using vcpkg with x64-windows triplet
find_package(fmt CONFIG REQUIRED)
find_package(SndFile CONFIG REQUIRED)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(OLaF ${SOURCES})

target_link_libraries(OLaF PRIVATE
    fmt::fmt
    SndFile::sndfile
)
