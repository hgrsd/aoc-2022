add_executable(day1 day1.c)
target_compile_options(day1 PUBLIC "-Wall")
target_link_libraries(day1 common)
target_include_directories(day1 PUBLIC "${PROJECT_SOURCE_DIR}/shared")

add_executable(day2 day2.c)
target_compile_options(day2 PUBLIC "-Wall")
target_link_libraries(day2 common)
target_include_directories(day2 PUBLIC "${PROJECT_SOURCE_DIR}/shared")
