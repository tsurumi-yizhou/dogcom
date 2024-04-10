cmake_minimum_required(VERSION 3.28.0)
project(dogcom)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)
file(GLOB_RECURSE SOURCE src/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCE})

find_package(Boost REQUIRED system log)
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost Boost::system Boost::log)

find_package(cryptopp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE cryptopp::cryptopp)