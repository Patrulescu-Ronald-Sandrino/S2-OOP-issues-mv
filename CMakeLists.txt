cmake_minimum_required(VERSION 3.22)
project(issues_mv)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(issues_mv src/main.cpp)
target_link_libraries(issues_mv
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

