cmake_minimum_required(VERSION 3.11.0 FATAL_ERROR)

project(boblamp)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

set(SOURCE_FILES main.cpp 
                 icons.qrc)

add_executable(${CMAKE_PROJECT_NAME} WIN32 ${SOURCE_FILES})

target_link_libraries(${CMAKE_PROJECT_NAME} Qt5::Widgets Qt5::Network Qt5::Core Qt5::Gui )

target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_14)

if(WIN32)
    # Load up the location of our found libs for copying
    get_target_property(QtCore_Location Qt5::Core LOCATION)
    get_target_property(QtGui_Location Qt5::Gui LOCATION)
    get_target_property(QtWidgets_Location Qt5::Widgets LOCATION)
    get_target_property(QtNetwork_Location Qt5::Network LOCATION)

    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_if_different ${QtCore_Location} $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
    )

    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_if_different ${QtGui_Location} $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
    )

    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_if_different ${QtWidgets_Location} $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
    )

    add_custom_command(TARGET ${CMAKE_PROJECT_NAME} POST_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy_if_different ${QtNetwork_Location} $<TARGET_FILE_DIR:${CMAKE_PROJECT_NAME}>
    )
endif()



