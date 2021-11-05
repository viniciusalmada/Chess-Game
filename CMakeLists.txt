cmake_minimum_required(VERSION 3.21)

# set the project name
project(Chess-Game)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

include_directories(include)

add_definitions(-DWORKING_DIR="${CMAKE_SOURCE_DIR}")

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(LibsModule
	include/app.h src/app.cpp
	include/board.h src/board.cpp
	include/canvas.h src/canvas.cpp
	include/coordinate.h src/coordinate.cpp
	include/game_app.h src/game_app.cpp
	include/gl_utils.h src/gl_utils.cpp
	include/hash_utl.h
	include/image_loader.h src/image_loader.cpp
	include/main_window.h src/main_window.cpp
	include/numeric_utils.h src/numeric_utils.cpp
	include/sp_string.h src/sp_string.cpp
	include/piece.h src/piece.cpp
	include/player.h
)

target_link_libraries(LibsModule iup iupgl im GLEW GL)

add_executable(Chess-Game 
	src/main.cpp)

	
target_link_libraries(Chess-Game LibsModule)
