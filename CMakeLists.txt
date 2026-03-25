cmake_minimum_required(VERSION 3.16)

project(FranKanoid VERSION 0.1)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(ENABLE_ASAN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")
endif()
option(ENABLE_ASAN "Enable AddressSanitizer" OFF)

include(FetchContent)

#TODO dependencies must be available locally on ZIP
# Dependencies
FetchContent_Declare(
	SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG        2.6.1
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
# avoid terminal window spawning Windows
if(WIN32)
	target_link_options(FranKanoid PRIVATE "/SUBSYSTEM:WINDOWS")
endif()

# This is needed to link SFML statically on windows
if(WIN32)
	target_compile_definitions(FranKanoid PUBLIC SFML_STATIC)
endif()

#TODO extra MacOS compatible?