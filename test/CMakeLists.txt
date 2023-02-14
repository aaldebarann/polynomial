set(target polynomial_test)

file(GLOB hdrs "*.h*" "../include/*.cpp")
file(GLOB srcs "*.cpp" "../src/*.cpp")

add_executable(${target} ${srcs} ${hdrs})
target_link_libraries(${target} gtest)
