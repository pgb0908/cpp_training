add_executable(thread_wrapper main.cpp)

add_library(thread
        ThreadFactory.cpp
        ThreadImpl.cpp
)

set(CMAKE_CXX_FLAGS -pthread)

target_link_libraries(thread_wrapper thread)