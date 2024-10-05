cmake_minimum_required(VERSION 3.16)
project(Polynomials LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    app/Polynomials.ico
    main.cpp

    
    frontend/badaba.txt

    frontend/includes/main_window.h
    frontend/includes/qt_headers.h

    frontend/source/base_operations.cpp
    frontend/source/base_table.cpp
    frontend/source/main_window.cpp
    frontend/source/other_operations.cpp
    frontend/source/polynomial_operations.cpp
    frontend/source/push_to_base.cpp
    frontend/source/two_polynomials_operations.cpp


    backend/includes/fraction.h
    backend/includes/my_base.h
    backend/includes/polynomial.h
    backend/includes/polynomial_node.h

    backend/source/fraction.cpp
    backend/source/polynomial.cpp
    backend/source/polynomial_node.cpp
)

qt_add_executable(Polynomials ${PROJECT_SOURCES})

set_target_properties(Polynomials
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(Polynomials
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
