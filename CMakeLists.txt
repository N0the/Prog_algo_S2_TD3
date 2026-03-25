cmake_minimum_required(VERSION 3.10)

project(TD03)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*.cpp)

foreach(f ${MY_SOURCES})
    get_filename_component(namefile ${f} NAME_WE)
    add_executable(${namefile} ${f})
    target_compile_features(${namefile} PRIVATE cxx_std_17)
endforeach()

