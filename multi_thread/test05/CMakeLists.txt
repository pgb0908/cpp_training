find_package(Threads)


add_executable(test05 main.cpp)
target_link_libraries(test05 Threads::Threads)