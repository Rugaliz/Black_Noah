cmake_minimum_required(VERSION 3.16)

project(BlackNoah VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Prefer Qt6 if available, fall back to Qt5
find_package(Qt6 QUIET COMPONENTS Widgets Core)
if(NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Widgets Core REQUIRED)
endif()

add_executable(blacknoah
    launchmethods.cpp
    main.cpp
    mainwindow.cpp
    resourced.qrc
)

target_include_directories(blacknoah PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

if(TARGET Qt6::Widgets)
    target_link_libraries(blacknoah PRIVATE Qt6::Widgets Qt6::Core)
else()
    target_link_libraries(blacknoah PRIVATE Qt5::Widgets Qt5::Core)
endif()
