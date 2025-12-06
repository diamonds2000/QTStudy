cmake_minimum_required(VERSION 3.16)

project(QTStudy VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add debug-specific compiler flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Gui)

qt6_add_resources(RESOURCE_FILES resources.qrc)

add_executable(QTStudy
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/drawview.cpp
    src/drawview.h
    ${RESOURCE_FILES}
)

target_link_libraries(QTStudy PRIVATE 
    Qt6::Core
    Qt6::Widgets
    Qt6::Gui
)

target_sources(QTStudy PRIVATE ${RESOURCE_FILES})

# set_target_properties(QTStudy PROPERTIES
#     WIN32_EXECUTABLE ON
#     MACOSX_BUNDLE ON
# )