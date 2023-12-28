SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(schedular main.cpp
dispatcher.cpp
request.cpp
worker.cpp)