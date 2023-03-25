set(target ${POL_LIBRARY})

file(GLOB hdrs "*.h*" "../include/*.cpp")
file(GLOB srcs "*.cpp" "../src/*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} ${LIBRARY_DEPS})