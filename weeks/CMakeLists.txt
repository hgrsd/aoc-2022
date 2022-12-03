add_executable(week1 week1.c)
target_compile_options(week1 PUBLIC "-Wall")
target_link_libraries(week1 common)
target_include_directories(week1 PUBLIC "${PROJECT_SOURCE_DIR}/shared")