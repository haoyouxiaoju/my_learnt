cmake_minimum_required(VERSION 3.16)
project(DisplayVideo LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 启用 Qt 资源支持
set(CMAKE_AUTORCC ON)  # 必须开启(否则qrc文件无法参与编译)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)
find_package(Qt6 REQUIRED COMPONENTS MultimediaWidgets)
find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    displayvideo.ui
    displayvideo.h
    displayvideo.cpp
    videocontrolbar.ui
    videocontrolbar.h
    videocontrolbar.cpp
)

set(PROJECT_QRC_SOURCES
    qss.qrc
)

qt_add_executable(${PROJECT_NAME} ${PROJECT_SOURCES} qss.qrc)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt6::Multimedia
        Qt6::MultimediaWidgets
        Qt6::Quick
)

