cmake_minimum_required(VERSION 3.7)
project(contnet)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

set(SOURCE_FILES main.cpp managed.cpp managed.h manager.cpp manager.h dockInt.cpp dockInt.h mainwindow.cpp mainwindow.h qcontainerwidget.cpp qcontainerwidget.h dialognewcont.cpp dialognewcont.h qcontainerwidgetexam.cpp qcontainerwidgetexam.h qcontconnectednetwidget.cpp qcontconnectednetwidget.h qnetworkwidget.cpp qnetworkwidget.h dialogaddnet.cpp dialogaddnet.h dialognewnet.cpp dialognewnet.h)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)

add_executable(contnet ${SOURCE_FILES})
target_link_libraries(contnet Qt5::Core Qt5::Widgets Qt5::Gui)
