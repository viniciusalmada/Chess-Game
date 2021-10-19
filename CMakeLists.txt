cmake_minimum_required(VERSION 3.10)

# set the project name
project(Chess-Game)

include_directories(include)

add_compile_definitions(GLEW_STATIC)

# add the executable
add_executable(Chess-Game 
	src/main.cpp
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
	)

find_library(project_libraries glew ${P iup im GL)

target_link_libraries(Chess-Game ${project_libraries})
