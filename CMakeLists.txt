cmake_minimum_required(VERSION 3.20)
project(app)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include(cmake/config_sqlite3.cmake)

function(setup_target TARGET_NAME)
    target_link_libraries(${TARGET_NAME} PUBLIC Qt6::Widgets)
    set_target_properties(${TARGET_NAME} PROPERTIES AUTOUIC_SEARCH_PATHS "./src/frontend")
endfunction()

add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/MainWindow.cpp 
    include/MainWindow.hpp 
    include/models/DatabaseModel.hpp 
    src/models/DatabaseModel.cpp 
    include/MathOperationsRecordsWidget.hpp
    src/MathOperationsRecordsWidget.cpp
)

config_sqlite3(${PROJECT_NAME}) 
setup_target(${PROJECT_NAME})