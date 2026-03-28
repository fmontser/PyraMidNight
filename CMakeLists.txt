cmake_minimum_required(VERSION 3.16)

project(FranKanoid VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_ASAN "Enable AddressSanitizer" OFF)
if(ENABLE_ASAN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
endif()

include(FetchContent)

#TODO dependencies must be available locally on ZIP
# Dependencies
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG        3.0.2
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

#TODO Must work on Windows.
if(WIN32)
	# avoid terminal window spawning Windows
	target_link_options(FranKanoid PRIVATE "/SUBSYSTEM:WINDOWS")
	# This is needed to link SFML statically on windows
	target_compile_definitions(FranKanoid PUBLIC SFML_STATIC)
endif()

# Assets copy
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

#TODO extra MacOS compatible?