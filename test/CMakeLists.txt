set(target ${POL_TESTS})

file(GLOB hdrs "*.h*" "../include/*.cpp")
file(GLOB srcs "*.cpp" "../src/*.cpp")

add_executable(${target} ${srcs} ${hdrs} ../include/calculator.cpp ../include/calculator.h)
target_link_libraries(${target} gtest)
