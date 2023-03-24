set(target ${POL_SRC})

file(GLOB hdrs "*.h*" "${POL_INCLUDE}*.cpp")
file(GLOB srcs "*.cpp" )

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} ${POL_LIBRARY})