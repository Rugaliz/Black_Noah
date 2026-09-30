cmake_minimum_required(VERSION 3.16)

project(BlackNoah VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

option(BUILD_TESTING "Build the unit tests" ON)

# Prefer Qt6 if available, fall back to Qt5 (5.14 or newer)
find_package(Qt6 QUIET COMPONENTS Widgets Core)
if(Qt6_FOUND)
    set(QT_NS Qt6)
else()
    find_package(Qt5 5.14 COMPONENTS Widgets Core REQUIRED)
    set(QT_NS Qt5)
endif()

# Launch logic without any UI dependency, shared by the app and the tests
add_library(blacknoah_core STATIC
    mamelauncher.cpp
    mamelauncher.h
)
target_include_directories(blacknoah_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(blacknoah_core PUBLIC ${QT_NS}::Core)

add_executable(blacknoah
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    systems.cpp
    systems.h
    resourced.qrc
)
target_link_libraries(blacknoah PRIVATE blacknoah_core ${QT_NS}::Widgets)

if(BUILD_TESTING)
    find_package(${QT_NS} QUIET COMPONENTS Test)
    if(${QT_NS}_Test_FOUND OR TARGET ${QT_NS}::Test)
        enable_testing()
        add_executable(tst_mamelauncher tests/tst_mamelauncher.cpp)
        target_link_libraries(tst_mamelauncher PRIVATE blacknoah_core ${QT_NS}::Test)
        add_test(NAME tst_mamelauncher COMMAND tst_mamelauncher)
    endif()
endif()
