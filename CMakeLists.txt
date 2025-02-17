cmake_minimum_required(VERSION 3.16)

project(TodoList VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Sql)



set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        taskwidget.h taskwidget.cpp taskwidget.ui
        taskcreationwindow.h taskcreationwindow.cpp taskcreationwindow.ui
        task.h
        taskeditionwindow.h taskeditionwindow.cpp taskeditionwindow.ui
        tasklist.h tasklist.cpp
        filter.h filter.cpp filter.ui
        dbmanager.h dbmanager.cpp
    )


add_executable(TodoList
    ${PROJECT_SOURCES}
)

target_include_directories(TodoList PRIVATE ./)

target_link_libraries(TodoList PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(TodoList PRIVATE Qt6::Sql)

set_target_properties(TodoList PROPERTIES
    ${BUNDLE_ID_OPTION}
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS TodoList
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

