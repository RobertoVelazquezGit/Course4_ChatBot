cmake_minimum_required(VERSION 3.11.3)

set(CMAKE_CXX_STANDARD 17)

project(Membot)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

file(GLOB project_SRCS src/*.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "debug")
    add_definitions(-DMY_IMAGES_PATH_DEBUG)
endif()

add_executable(membot ${project_SRCS})
target_link_libraries(membot ${wxWidgets_LIBRARIES})
target_include_directories(membot PRIVATE ${wxWidgets_INCLUDE_DIRS})
# Asegurarse de incluir los archivos de encabezado de la carpeta src
target_include_directories(membot PRIVATE ${CMAKE_SOURCE_DIR}/src)


