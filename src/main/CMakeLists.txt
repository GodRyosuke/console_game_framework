add_library(
	wander_game_lib STATIC
	Game.cpp
)
target_include_directories(wander_game_lib PUBLIC "${PROJECT_SOURCE_DIR}/include")

