add_executable(week1 week1.c)
target_link_libraries(week1 common)
target_include_directories(week1 PUBLIC "${PROJECT_SOURCE_DIR}/shared")