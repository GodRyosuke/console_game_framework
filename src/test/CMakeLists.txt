add_executable(
	wander_game_test
	main.cpp
)
target_link_libraries(
	wander_game_test PRIVATE
	wander_game_lib
)
target_include_directories(wander_game_test PUBLIC "${PROJECT_SOURCE_DIR}/include")

add_custom_command(
	TARGET wander_game_test
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${PROJECT_SOURCE_DIR}/GameData/ $<TARGET_FILE_DIR:wander_game_test>/GameData/
)


add_test(NAME WanderLibTests COMMAND wander_lib_tests)