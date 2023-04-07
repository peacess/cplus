cmake_minimum_required(VERSION 3.22)
project(cplus)

set(CMAKE_CXX_STANDARD 20)

# set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
# set(Boost_USE_DEBUG_LIBS         OFF) # ignore debug libs and 
# set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs 
# set(Boost_USE_MULTITHREADED      ON)
# set(Boost_USE_STATIC_RUNTIME    OFF) 
# find_package(Boost 1.74 COMPONENTS date_time filesystem system ...)
# if(Boost_FOUND)   
#     include_directories(${Boost_INCLUDE_DIRS})
#     add_executable(foo foo.cc)   
#     target_link_libraries(foo ${Boost_LIBRARIES})
# endif()

add_executable(ordering thread_/ordering_.cpp)