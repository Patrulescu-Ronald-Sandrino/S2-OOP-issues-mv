cmake_minimum_required(VERSION 3.22)
project(issues_mv)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

file(COPY data/users.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY data/issues.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(issues_mv src/main.cpp src/domain/User.cpp src/domain/User.h src/ui/UserWindow.cpp src/ui/UserWindow.h src/domain/Issue.cpp src/domain/Issue.h src/repository/IssueRepository.cpp src/repository/IssueRepository.h src/ui/IssuesModel.cpp src/ui/IssuesModel.h)
target_link_libraries(issues_mv
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

