cmake_minimum_required(VERSION 3.4.1)
project(androidvncserver)
add_executable(
    androidvncserver
    droidvncserver.c
    gui.c
    inputMethods/input.c
    screenMethods/adb.c
    screenMethods/framebuffer.c
    screenMethods/gralloc.c
    screenMethods/flinger.c
    suinput/suinput.c
)
ADD_SUBDIRECTORY(libvncserver)

target_link_libraries(androidvncserver vncserver log)
include_directories(
    ${PROJECT_SOURCE_DIR}/libvncserver
    ${PROJECT_BINARY_DIR}/libvncserver
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/suinput
    ${PROJECT_SOURCE_DIR}/screenMethods
    ${PROJECT_SOURCE_DIR}/linux
    ${PROJECT_SOURCE_DIR}/inputMethods
    ${PROJECT_SOURCE_DIR}
)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DNOAPP")
