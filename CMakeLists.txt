cmake_minimum_required(VERSION 3.5)

project(MPMCMQ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Threads REQUIRED)

set(include_dir ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(source_dir  ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE hdr ${include_dir}/${CMAKE_PROJECT_NAME}/*.h)
file(GLOB_RECURSE src ${source_dir}/*.cpp)


add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
    ${hdr}
    ${src}
)

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${include_dir})
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
    Threads::Threads
)
