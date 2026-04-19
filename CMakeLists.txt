cmake_minimum_required(VERSION 3.16)

project(PyraMidNight VERSION 0.1)
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
	DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(SFML)

# BINARIES
set(APP_SOURCES
	src/main.cpp
	src/Game.cpp
	src/Managers/AudioManager.cpp
	src/Managers/InputManager.cpp
	src/Managers/RenderManager.cpp
	src/Managers/ResourceManager.cpp
	src/Managers/UserDataManager.cpp
	src/ScreenViews/ScreenView.cpp
	src/ScreenViews/MenuScreenView.cpp
	src/ScreenViews/TitleScreenView.cpp
	src/ScreenViews/RoundScreenView.cpp
	src/ScreenViews/EndScreenView.cpp
	src/GameObjects/Bumper.cpp
	src/GameObjects/Ball.cpp
	src/GameObjects/Block.cpp
	src/GameObjects/Obstacle.cpp
	src/GameObjects/Cursor.cpp
	src/GameObjects/PolySound.cpp
	src/GameObjects/Spawner.cpp
	src/GameObjects/PowerUps/PowerUp.cpp
	src/GameObjects/PowerUps/ExtraScorePuP.cpp
	src/GameObjects/PowerUps/ExtraCreditPuP.cpp
	src/GameObjects/PowerUps/GhostPuP.cpp
	src/GameObjects/PowerUps/MagicPuP.cpp
	src/GameObjects/Misiles/Misile.cpp
	src/GameObjects/Misiles/HolyMisile.cpp
	src/RenderEffects/RenderEffect.cpp
	src/RenderEffects/ScreenShake.cpp
	src/RenderEffects/Blink.cpp
	src/RenderEffects/Flash.cpp
	src/RenderEffects/BreathColor.cpp
)

set(APP_LIBS
	sfml-system
	sfml-window
	sfml-graphics
	sfml-audio
)

add_executable(PyraMidNight ${APP_SOURCES})

if(MSVC)
	# disabled some type conversion warnings to avoid explicit casting everywhere
	target_compile_options(PyraMidNight PRIVATE /W4 /WX /wd4244 /wd4267)
else()
	target_compile_options(PyraMidNight PRIVATE -Wall -Wextra -Werror)
endif()

target_include_directories(PyraMidNight PUBLIC include/)
target_include_directories(PyraMidNight PUBLIC include/Data)
target_include_directories(PyraMidNight PUBLIC include/GameObjects)
target_include_directories(PyraMidNight PUBLIC include/GameObjects/PowerUps)
target_include_directories(PyraMidNight PUBLIC include/GameObjects/Misiles)
target_include_directories(PyraMidNight PUBLIC include/Interfaces)
target_include_directories(PyraMidNight PUBLIC include/ScreenViews)
target_include_directories(PyraMidNight PUBLIC include/Managers)
target_include_directories(PyraMidNight PUBLIC include/RenderEffects)
target_link_libraries(PyraMidNight PRIVATE ${APP_LIBS})

# MultiPlatform setting

if(WIN32)
	# needed for windows main type
	target_link_libraries(PyraMidNight PRIVATE sfml-main)
	# avoid terminal window spawning Windows
	target_link_options(PyraMidNight PRIVATE "/SUBSYSTEM:WINDOWS")
	target_compile_definitions(PyraMidNight PUBLIC SFML_STATIC)
endif()

# Assets copy
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

#TODO extra MacOS compatible?