cmake_minimum_required(VERSION 3.5)

project(painter LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)

if(ANDROID)
  add_library(painter SHARED
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    progreswidget.h
  )
else()
  add_executable(painter
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui

    progreswidget.cpp
  )
endif()

target_link_libraries(painter PRIVATE Qt5::Widgets)
