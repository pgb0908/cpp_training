find_package(Threads)


add_executable(test04 main.cpp)
target_link_libraries(test04 Threads::Threads)