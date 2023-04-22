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
add_executable(operator lang/overload_/class_8.cpp)

FILE(GLOB static_inline_src ./lang/static_inline/*.cpp)
add_executable(static_inline ${static_inline_src})   

FILE(GLOB t_h_cpp_src ./t/h_cpp/*.cpp)
add_executable(t_h_cpp ${t_h_cpp_src})  

FILE(GLOB pimpl_src ./lang/pimpl/*.cpp)
add_executable(pimpl ${pimpl_src})  