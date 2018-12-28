cmake_minimum_required(VERSION 2.8)
project(flatbuffers_demo)

set(Boost_LIB "C:/boost-build/lib")
set(BOOST_ROOT "C:/boost-build/include/boost-1_69")

find_package( Boost REQUIRED )

message("Boost_FOUND='${Boost_INCLUDE_DIRS}'")
message("Boost_LIBS='${Boost_LIBS}'")

include_directories(${Boost_INCLUDE_DIRS} 
    third_party/flatbuffers/include
    schema
    communication)
add_executable(${PROJECT_NAME} "main.cpp" communication/server.cpp)
target_link_libraries(${PROJECT_NAME} ws2_32
    ${OpenCV_LIBS} ${Boost_LIB}/libboost_thread-mgw81-mt-x64-1_69.a
    ${OpenCV_LIBS} ${Boost_LIB}/libboost_system-mgw81-mt-x64-1_69.a
)