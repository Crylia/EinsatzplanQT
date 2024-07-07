cmake_minimum_required(VERSION 3.5)

project(EinsatzplanQT VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR
	CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	add_compile_options(-Wall -Wextra -pedantic)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_options(/W4)
endif()

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Svg Core Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Svg Core Sql)

file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)
file(GLOB_RECURSE PROJECT_HEADERS src/*.hpp)
file(GLOB_RECURSE PROJECT_RESOURCES assets/resources.qrc)

add_executable(EinsatzplanQT
	${PROJECT_SOURCES}
	${PROJECT_HEADERS}
	${PROJECT_RESOURCES}
)

target_link_libraries(EinsatzplanQT PRIVATE
	Qt${QT_VERSION_MAJOR}::Widgets
	Qt${QT_VERSION_MAJOR}::Svg
	Qt${QT_VERSION_MAJOR}::Core
	Qt${QT_VERSION_MAJOR}::Sql
	fmt
	pqxx
	stdc++fs
)

install(TARGETS EinsatzplanQT DESTINATION /usr/bin)

set(DESKTOP_FILE_CONTENT "
[Desktop Entry]
Name=EinsatzplanQT
Exec=/usr/bin/EinsatzplanQT
Icon=calendar
Type=Application
Categories=Utility
;")

set(DESKTOP_FILE_PATH "${CMAKE_BINARY_DIR}/EinsatzplanQT.desktop")
file(WRITE ${DESKTOP_FILE_PATH} ${DESKTOP_FILE_CONTENT})
install(FILES ${DESKTOP_FILE_PATH} DESTINATION /usr/share/applications)
