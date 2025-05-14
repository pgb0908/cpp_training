find_package(Threads)


add_executable(test04 promise.cpp)
target_link_libraries(test04 Threads::Threads)