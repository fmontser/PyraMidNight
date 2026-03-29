cmake_minimum_required(VERSION 3.16)

project(FranKanoid VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# SFML local dependencies
set(SFML_STATIC_LIBRARIES ON CACHE BOOL "" FORCE)
set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(SFML_INSTALL_PKGCONFIG_FILES OFF CACHE BOOL "" FORCE)
set(SFML_ZIP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/external/SFML-3.0.2.zip")

# address sanitizer
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
if(ENABLE_ASAN)
	if(MSVC)
		# windows
		add_compile_options(/fsanitize=address /Zi)
		add_link_options(/INCREMENTAL:NO)
		message(STATUS "AddressSanitizer enabled (MSVC)")
	else()
		# linux
		add_compile_options(-fsanitize=address -g)
		add_link_options(-fsanitize=address)
		message(STATUS "AddressSanitizer enabled (GCC)")
	endif()
endif()

# Unzip SFML
include(FetchContent)
FetchContent_Declare(
	SFML
	URL "${SFML_ZIP_PATH}"
)
FetchContent_MakeAvailable(SFML)


# BINARIES
set(APP_SOURCES
	src/main.cpp
	src/Game.cpp
	src/RenderManager.cpp
	src/InputManager.cpp
	src/ScreenView.cpp
	src/TitleScreenView.cpp
	src/RoundScreenView.cpp
	src/EndScreenView.cpp
	src/Bumper.cpp
	src/Ball.cpp
	src/Block.cpp
	src/Cursor.cpp
)

set(APP_LIBS
	sfml-system
	sfml-window
	sfml-graphics
	sfml-audio #TODO remove audio if out of scope/time
)

add_executable(FranKanoid ${APP_SOURCES})

target_include_directories(FranKanoid PUBLIC include)
target_link_libraries(FranKanoid PRIVATE ${APP_LIBS})

# MultiPlatform setting

if(WIN32)
	# needed for windows main type
	target_link_libraries(FranKanoid PRIVATE sfml-main)
	# avoid terminal window spawning Windows
	target_link_options(FranKanoid PRIVATE "/SUBSYSTEM:WINDOWS")
	target_compile_definitions(FranKanoid PUBLIC SFML_STATIC)
endif()

# Assets copy
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

#TODO extra MacOS compatible?