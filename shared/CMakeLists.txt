add_library(common common.c common.h node.c node.h)
target_compile_options(common PUBLIC "-Wall")