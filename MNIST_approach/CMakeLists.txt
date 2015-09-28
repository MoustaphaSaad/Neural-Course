cmake_minimum_required(VERSION 3.2)
project(MNIST_approach)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("./inc")
set(SOURCE_FILES main.cpp)

add_executable(MNIST_approach ${SOURCE_FILES} src/Connection.cpp inc/Connection.h src/Weight.cpp inc/Weight.h inc/Neuron.hpp src/Neuron.cpp inc/Layer.hpp src/Layer.cpp inc/Net.hpp src/Net.cpp inc/Global_Prop.hpp)