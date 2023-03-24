set(target ${POL_INC})

file(GLOB hdrs "*.h*" "../include/*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} ${LIBRARY_DEPS})