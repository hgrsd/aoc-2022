add_library(common common.c common.h list.c list.h charset.c charset.h tree.c tree.h)
target_compile_options(common PUBLIC "-Wall")