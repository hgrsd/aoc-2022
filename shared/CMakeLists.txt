add_library(common common.c common.h node.c node.h list.c list.h charset.c charset.h)
target_compile_options(common PUBLIC "-Wall")