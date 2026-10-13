cmake_minimum_required(VERSION 3.16)
project(ERP_Estoque_Vendas VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

add_executable(erp_estoque_vendas
    src/main.cpp
    src/database/Database.cpp
    src/database/Database.h
    src/services/SalesService.cpp
    src/services/SalesService.h
    src/ui/MainWindow.cpp
    src/ui/MainWindow.h
)

target_link_libraries(erp_estoque_vendas PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

if(MSVC)
    target_compile_options(erp_estoque_vendas PRIVATE /W4)
else()
    target_compile_options(erp_estoque_vendas PRIVATE -Wall -Wextra -Wpedantic)
endif()
